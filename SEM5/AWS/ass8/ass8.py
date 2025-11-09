from pyspark.sql import SparkSession
from pyspark.sql.functions import col, count, trim
from pyspark.sql.types import DoubleType
from pyspark.ml.feature import VectorAssembler
from pyspark.ml.clustering import KMeans

# Initialize Spark session
spark = SparkSession.builder.appName("AdultDatasetAnalysis").getOrCreate()

# Load dataset with column names
cols = [
    "age", "workclass", "fnlwgt", "education", "education_num", "marital_status",
    "occupation", "relationship", "race", "sex", "capital_gain", "capital_loss",
    "hours_per_week", "native_country", "income"
]

df = spark.read.csv("adult.data", header=False, inferSchema=False).toDF(*cols)

# --- Data Cleaning & Type Conversion ---
df = df.select([trim(col(c)).alias(c) for c in df.columns])  # remove extra spaces

# Cast numeric columns to DoubleType (handles decimals safely)
df = df.withColumn("age", col("age").cast(DoubleType())) \
       .withColumn("education_num", col("education_num").cast(DoubleType())) \
       .withColumn("hours_per_week", col("hours_per_week").cast(DoubleType())) \
       .withColumn("capital_gain", col("capital_gain").cast(DoubleType())) \
       .withColumn("capital_loss", col("capital_loss").cast(DoubleType())) \
       .withColumn("fnlwgt", col("fnlwgt").cast(DoubleType()))

print("\n--- Schema After Type Conversion ---")
df.printSchema()

# --- 1. KMeans Clustering on age, education_num, hours_per_week ---
print("\n--- 1. KMeans Clustering on age, education_num, hours_per_week ---")

assembler = VectorAssembler(
    inputCols=["age", "education_num", "hours_per_week"],
    outputCol="features"
)
data = assembler.transform(df)

kmeans = KMeans(k=3, seed=1)
model = kmeans.fit(data)
clusters = model.transform(data)

print("\nSample clustered data:")
clusters.select("age", "education_num", "hours_per_week", "prediction").show()

# --- 3(i). Country with highest number of adults except USA ---
print("\n--- 3(i). Country with highest number of adults except USA ---")

df.filter(col("native_country") != "United-States") \
  .groupBy("native_country").count() \
  .orderBy(col("count").desc()) \
  .show(1)

# --- 3(ii). Number of people with at least Masters and working in Tech-support ---
print("\n--- 3(ii). Number of people with at least Masters and working in Tech-support ---")

masters_plus = ["Masters", "Doctorate", "Prof-school"]
count_masters_tech = df.filter(
    (col("education").isin(masters_plus)) &
    (col("occupation") == "Tech-support")
).count()
print(f"Count: {count_masters_tech}")

# --- 3(iii). Number of unmarried males working in Local-govt ---
print("\n--- 3(iii). Number of unmarried males working in Local-govt ---")

unmarried = ["Never-married", "Divorced", "Separated", "Widowed"]
count_unmarried_localgov = df.filter(
    (col("sex") == "Male") &
    (col("workclass") == "Local-gov") &
    (col("marital_status").isin(unmarried))
).count()
print(f"Count: {count_unmarried_localgov}")

# Stop Spark session
spark.stop()
