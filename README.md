Title: Seat Allocation in colleges

Description:

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

Technologies / Softwares need to be installed :
1. g++ compiler
2. python compiler
3. Facility to run html, css 
(VISUAL STUDIO CODE EXTENSIONS USED SO FAR)

ASSUMPTIONS:
1. We need to get choices input from a website, we assumed choices are written to a text file and processed further
2. The Student list of every college is written in a separate file which may be used to display in website 
