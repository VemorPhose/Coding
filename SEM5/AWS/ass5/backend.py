import os
from dotenv import load_dotenv
from fastapi import FastAPI, Depends, HTTPException, status
from pydantic import BaseModel, EmailStr
from sqlalchemy import create_engine, Column, Integer, String, Text, TIMESTAMP
from sqlalchemy.orm import sessionmaker, Session, declarative_base
from sqlalchemy.sql import func
import time

# Wait a moment for network/DNS resolution after startup
time.sleep(10) 
load_dotenv()

# --- Database Configuration & SQLAlchemy Setup ---
DATABASE_URL = (
    f"mysql+pymysql://{os.getenv('DB_USER')}:{os.getenv('DB_PASSWORD')}"
    f"@{os.getenv('DB_ENDPOINT')}:3306/feedbackdb"
)
engine = create_engine(DATABASE_URL)
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)
Base = declarative_base()

# --- SQLAlchemy Model & Pydantic Schemas ---
class Feedback(Base):
    __tablename__ = "feedback"
    id = Column(Integer, primary_key=True)
    name = Column(String(100), nullable=False)
    email = Column(String(100))
    comment = Column(Text, nullable=False)
    created_at = Column(TIMESTAMP, server_default=func.now())

class FeedbackBase(BaseModel): # Used for creating feedback
    name: str
    email: EmailStr | None = None
    comment: str

class FeedbackResponse(FeedbackBase): # Used for returning feedback
    id: int
    created_at: str
    class Config: from_attributes = True

# --- FastAPI App ---
app = FastAPI(title="Concise Feedback API")

@app.on_event("startup")
def on_startup():
    """Create database table on startup if it doesn't exist."""
    Base.metadata.create_all(bind=engine)

def get_db():
    db = SessionLocal()
    try: yield db
    finally: db.close()

@app.post("/feedback", response_model=FeedbackResponse, status_code=status.HTTP_201_CREATED)
def create_feedback(feedback_data: FeedbackBase, db: Session = Depends(get_db)):
    """Receives feedback and stores it in the RDS database."""
    new_feedback = Feedback(**feedback_data.model_dump())
    db.add(new_feedback)
    db.commit()
    db.refresh(new_feedback)
    return new_feedback

@app.get("/feedback", response_model=list[FeedbackResponse])
def get_all_feedback(db: Session = Depends(get_db)):
    """Retrieves all feedback entries from the RDS database."""
    return db.query(Feedback).order_by(Feedback.id.desc()).all()
