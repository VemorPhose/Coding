student_grades = {'ram': 9, 'shyam': 10, 'ganesh': 7, 'ramesh': 4}

# i
student = input("Enter student name to check grade: ")
if student in student_grades:
    print(f"{student} has scored {student_grades[student]} marks")
else:
    print(f"{student} is not found in the dictionary")

# ii
student = input("Enter student name to add to dict: ")
if student in student_grades:
    print(f"{student} already in the dictionary")
else:
    grade = int(input("Enter grade of student: "))
student_grades[student] = grade

# iii
student = input("Enter name of student to update grade: ")
if student in student_grades:
    grade = int(input("Enter updated grade: "))
    student_grades[student] = grade
else:
    print(f"{student} is not found in the dictionary")

# iv
for i in student_grades:
    if student_grades[i] > 5:
        print(f"{i} has passed with a grade of {student_grades[i]}")
