### 2.e.

Analysis for m=2:
  Silhouette Score: 0.2001
  Cluster sizes: [274 268 226]

Analysis for m=4:
  Silhouette Score: 0.0535
  Cluster sizes: [ 75 333 360]

### 2.f.

Cluster Centroids for m=2:
Cluster         Glucose         BMI             BloodPressure   Age            
Low Risk        103.60          62.85           27.72           26.95          
Borderline      120.96          71.11           34.98           30.15          
High Risk       141.60          75.77           33.20           44.15          

Normalized Centroids (z-scores):
Cluster         Glucose         BMI             BloodPressure   Age            
Low Risk        -0.5412         -0.3236         -0.5423         -0.5354        
Borderline      0.0021          0.1036          0.3786          -0.2628        
High Risk       0.6480          0.3444          0.1529          0.9282         

Cluster Centroids for m=4:
Cluster         Glucose         BMI             BloodPressure   Age            
Low Risk        117.58          68.09           31.56           31.83          
Borderline      128.13          71.48           32.92           36.29          
High Risk       117.29          67.99           31.51           31.72          

Normalized Centroids (z-scores):
Cluster         Glucose         BMI             BloodPressure   Age            
Low Risk        -0.1038         -0.0527         -0.0551         -0.1200        
Borderline      0.2265          0.1229          0.1183          0.2599         
High Risk       -0.1127         -0.0575         -0.0615         -0.1291

### 2.g.

Patient    Glucose    BMI        BP         Age        Assigned        Low Risk     Borderline   High Risk    Interpretation
--------------------------------------------------------------------------------------------------------------------------------------------
668        98.0       34.0       58.0       43.0       Borderline      0.3186       0.3781       0.3033       Uncertain, borderline
324        112.0      35.7       75.0       21.0       Borderline      0.2674       0.6361       0.0965       Moderate confidence
624        108.0      30.8       64.0       21.0       Low Risk        0.6931       0.2520       0.0549       Moderate confidence
690        107.0      24.6       80.0       34.0       Low Risk        0.4994       0.2926       0.2080       Uncertain
473        136.0      29.9       90.0       50.0       High Risk       0.1051       0.1638       0.7311       Moderate confidence
204        103.0      37.7       72.0       55.0       High Risk       0.1871       0.2869       0.5261       Moderate confidence
97         71.0       20.4       48.0       22.0       Low Risk        0.6465       0.2220       0.1315       Moderate confidence
336        117.0      33.8       0.0        44.0       Low Risk        0.3648       0.3279       0.3073       Uncertain, borderline
568        154.0      31.3       72.0       37.0       High Risk       0.1092       0.2447       0.6461       Moderate confidence
148        147.0      33.7       78.0       65.0       High Risk       0.1506       0.2119       0.6375       Moderate confidence

Clinical Insights:
--------------------------------------------------------------------------------
- Membership > 0.8: Strong classification confidence
- Membership 0.5-0.8: Moderate confidence, patient shows mixed characteristics
- Membership < 0.5: Uncertain, patient falls between multiple risk categories
- Close memberships (<0.2 difference): Patient at boundary between risk groups

### 2.h.

Number of uncertain patients: 276 (35.94%)

Sample of uncertain patients:
------------------------------------------------------------------------------------------------------------------------
Patient    Glucose    BMI        BP         Age        Low Risk     Borderline   High Risk    Max       
------------------------------------------------------------------------------------------------------------------------
2          183.0      23.3       64.0       32.0       0.2847       0.3104       0.4049       0.4049    
4          137.0      43.1       40.0       33.0       0.2656       0.4400       0.2944       0.4400    
7          115.0      35.3       0.0        29.0       0.3979       0.3415       0.2606       0.3979    
9          125.0      0.0        96.0       54.0       0.3462       0.2860       0.3679       0.3679    
11         168.0      38.0       74.0       34.0       0.1387       0.3663       0.4950       0.4950    
15         100.0      30.0       0.0        32.0       0.4260       0.3213       0.2527       0.4260    
18         103.0      43.3       30.0       33.0       0.3436       0.4037       0.2526       0.4037    
23         119.0      29.0       80.0       29.0       0.3602       0.4844       0.1554       0.4844    
29         117.0      34.1       92.0       38.0       0.1681       0.4087       0.4232       0.4232    
31         158.0      31.6       76.0       28.0       0.2054       0.4565       0.3382       0.4565    

Interpretation:
These patients exhibit characteristics that don't clearly align with any single
risk category, suggesting they may be transitioning between risk levels or have
atypical clinical profiles requiring individualized assessment.

### 2.i.

1. NUMBER OF PATIENTS BY CLUSTERING CERTAINTY:
--------------------------------------------------------------------------------
   Uncertain (max membership ≤ 0.5): 276 patients (35.94%)
   Certain (max membership ≥ 0.8): 492 patients (64.06%)
   Moderate (0.5 < max membership < 0.8): 0 patients (0.00%)

2. CLINICAL PARAMETERS COMPARISON:
--------------------------------------------------------------------------------
Parameter            Uncertain Mean       Certain Mean         Difference           % Difference   
-----------------------------------------------------------------------------------------------
Glucose              122.25               120.13               2.12                 1.77           %
BMI                  32.65                31.62                1.03                 3.25           %
BloodPressure        65.46                71.15                -5.70                -8.01          %

Standard Deviations:
-----------------------------------------------------------------------------------------------
Parameter            Uncertain Std        Certain Std          Variability Ratio   
-----------------------------------------------------------------------------------------------
Glucose              37.59                28.35                1.33                
BMI                  10.08                6.31                 1.60                
BloodPressure        28.08                11.48                2.45                

KEY FINDINGS:
--------------------------------------------------------------------------------
• Uncertain patients have higher Glucose (2.12 units, 1.8%)
• Uncertain patients have higher BMI (1.03 units, 3.2%)
• Uncertain patients have lower BloodPressure (5.70 units, 8.0%)

• Uncertain patients show 32.6% more variability in Glucose
• Uncertain patients show 59.9% more variability in BMI
• Uncertain patients show 144.5% more variability in BloodPressure