Title: Seat Allocation in colleges

Name of team members: 
1. Mohammed Abdul Akram (Roll number : 211120)
2. Harsha Vardhan Reddy Manam (Roll number : 211112)

Problem Statement:
Allocate seats to students in different colleges based on their ranks (both category and open rank). Also include reservation seats which are reserved to particular category only.Provide a facility for the colleges to have the ids of the students who got seat in their college and further no college should be able to see students of other college. 

Description / Methodology Details:

1. Generates user id, ranks and category ranks and stores in a text file
2. Gets the input of choices through a text file
3. Firstly stores all the data of user id's, categories and their respective ranks
4. While storing data is sorted based on ranks
5. A user defined data structure is created to store all the necessary information of an applicant 
6. Traverse's through the applicants and allocates seats based on their choices
7. First category students are allcoated seats based on their category ranks and available seats
8. Further all remaining applicants(who didnt receive a seat) are allocated seats based on the open rank
9. Function are written to check if seat is available or not and then allocate if available 
10. Students are then stored in relevant data structures such that every college's students are separated 
11. List of Students belonging to particular college are written in separate file
12. This is done so that college authority may sign in through user id and password and check list of students joined in their college in different branches
13. For simplicity the colleges are limited to 5, each college with 3 branches (CSE, ECE, MECH) with 30 seats per branch

ASSUMPTIONS:
1. We require data of user ids, category, category rank, open rank of students, we assumed the data is in a text file (info_category.txt) and is in the order of 
    ->User id
    ->Category
    ->Open Rank
    ->Category Rank
2. We require data of choices of students, we assumed the data is written into a text file (sample_choices.txt) and is in the order of:
    ->User id
    ->College choice 1
    ->Branch choice 1
    ->College choice 2
    ->Branch choice 2
    ->College choice 3
    ->Branch choice 3
3. We assumed that there are 5 colleges (IIT GOA, NIT CALICUT, NIT WARANGAL, IIIT TRICHY, IIIT RANCHI) and 3 branches (CSE, ECE, MECH) in each college with 30 seats per branch.
4. We assumed that user id and password for college to check the list of students joined in their college is same
    example: user id - IIIT_TRICHY password - IIIT_TRICHY

How to Run the program:
1. Write the data of two text files info_category.txt and sample_choices.txt 
2. Run the program logic.cpp
3. Run the html files
4. Output can be checked in the website using userid and password or can be verified in output text files



