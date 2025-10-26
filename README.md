# CS300
#JakeTheSnake(JMG3000)

What was the problem you were solving in the projects for this course?

The main problem I was solving in these projects was how to efficiently store, access, and manage course information for Computer Science advisors at ABC University (ABCU). Advisors needed a system to quickly load data from a file, validate it, and then display course information along with any prerequisites. Each milestone focused on implementing and improving this functionality using different data structures, vectors, binary search trees (BSTs), and hash tables, to explore how data organization impacts performance and design.

How did you approach the problem?

I approached the problem by first analyzing the requirements for storing and retrieving course data, then determining which data structure best suited those needs. In the first milestone, I used vectors for simplicity and linear traversal. The second milestone improved retrieval efficiency using a binary search tree, which allowed faster searching and in-order traversal for sorted output. In the third milestone, I implemented a hash table to achieve constant-time average lookup performance. Understanding these data structures was crucial because they directly affect how efficiently data can be inserted, searched, or displayed is all key to writing scalable and maintainable programs.

How did you overcome any roadblocks you encountered while going through the activities or project?

One major challenge was ensuring that prerequisite validation worked correctly across all data structures. For example, when loading course data from a file, I had to make sure that each prerequisite actually existed in the dataset. Debugging file parsing and data validation errors taught me to pay close attention to input formatting and to include error handling for invalid or missing data. I also encountered logic issues when implementing recursive insert and search functions in the BST milestone, which I resolved by breaking down the recursion step by step and testing smaller sections of code before combining them.

How has your work on this project expanded your approach to designing software and developing programs?

Working on these projects has strengthened my understanding of software design principles, especially modularity and abstraction. By designing pseudocode before implementing full C++ programs, I learned to separate data representation (structures like Course and Node) from data management (functions like loadCourses, searchCourse, and printAllCourses). It also reinforced how algorithm choice impacts performance and scalability — for instance, realizing how switching from a vector to a hash table drastically reduces search time.

How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

This project has made me more intentional about writing clean, readable, and reusable code. I now use consistent naming conventions, modular functions, and clear comments to make programs easier to understand and maintain. Designing the same program using multiple data structures taught me to think abstractly about functionality rather than being tied to a specific implementation. It also emphasized the importance of adaptability in writing code because of the evolvion of code as requirements change without needing a complete rewrite.
