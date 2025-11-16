import os
from flask import Flask, redirect, session, request, render_template_string
import requests
from urllib.parse import urlencode
from dotenv import load_dotenv

load_dotenv()

app = Flask(__name__)
app.secret_key = os.getenv("SECRET_KEY")

CLIENT_ID = os.getenv("GOOGLE_CLIENT_ID")
CLIENT_SECRET = os.getenv("GOOGLE_CLIENT_SECRET")
REDIRECT_URI = os.getenv("GOOGLE_REDIRECT_URI")

AUTH_ENDPOINT = "https://accounts.google.com/o/oauth2/v2/auth"
TOKEN_ENDPOINT = "https://oauth2.googleapis.com/token"
USERINFO_ENDPOINT = "https://www.googleapis.com/oauth2/v3/userinfo"

COMMENTS = []

HTML_TEMPLATE = """
<h2>Google Auth Demo (Restricted to @iiitg.ac.in)</h2>

{% if user %}
    <p>Welcome, {{ user['email'] }}!</p>

    <form action="/comment" method="post">
        <textarea name="comment" rows="4" cols="50" required></textarea><br>
        <button type="submit">Post Comment</button>
    </form>

    <h3>Comments:</h3>
    {% for c in comments %}
        <p><b>{{ c['email'] }}</b>: {{ c['comment'] }}</p>
    {% endfor %}

    <a href="/logout">Logout</a>

{% else %}
    <a href="/login">Login with Google</a>
{% endif %}
"""


@app.route("/")
def index():
    user = session.get("user")
    return render_template_string(HTML_TEMPLATE, user=user, comments=COMMENTS)


@app.route("/login")
def login():
    params = {
        "client_id": CLIENT_ID,
        "redirect_uri": REDIRECT_URI,
        "response_type": "code",
        "scope": "openid email profile",
        "access_type": "offline",
        "prompt": "consent",
    }
    return redirect(f"{AUTH_ENDPOINT}?{urlencode(params)}")


@app.route("/oauth/callback")
def oauth2callback():
    code = request.args.get("code")

    token_data = {
        "code": code,
        "client_id": CLIENT_ID,
        "client_secret": CLIENT_SECRET,
        "redirect_uri": REDIRECT_URI,
        "grant_type": "authorization_code",
    }

    token_response = requests.post(TOKEN_ENDPOINT, data=token_data).json()
    access_token = token_response.get("access_token")

    # Get user profile info
    headers = {"Authorization": f"Bearer {access_token}"}
    userinfo = requests.get(USERINFO_ENDPOINT, headers=headers).json()

    email = userinfo.get("email")

    # Restrict domain
    if not email.endswith("@iiitg.ac.in"):
        return "Access denied: Only @iiitg.ac.in users allowed."

    # Save authenticated user
    session["user"] = {
        "email": userinfo["email"],
        "name": userinfo.get("name"),
        "picture": userinfo.get("picture"),
    }

    return redirect("/")


@app.route("/comment", methods=["POST"])
def post_comment():
    if "user" not in session:
        return redirect("/login")

    comment_text = request.form.get("comment")

    COMMENTS.append({
        "email": session["user"]["email"],
        "comment": comment_text
    })

    return redirect("/")


@app.route("/logout")
def logout():
    session.clear()
    return redirect("/")


if __name__ == "__main__":
    app.run(debug=True)
