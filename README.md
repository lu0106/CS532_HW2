# CS532_HW2

# Reference my CS533 assignment

Name: Hung-Yi Lu
BlazerId: lu0106
Project #:Homework 2

To compile: use command "gcc hw2.c"

To run: use command: 
./a.out -S can add [path]
./a.out -S -s[size] can add [path]
./a.out -f[txt] can add [path]
./a.out -S -f[txt] can add [path]
./a.out -s[size] -f[txt] can add [path]
./a.out -t d(directory) can add [path]
./a.out -t f(file) can add [path]
./a.out -S -s[size] -t f(file) can add [path]


===========================================================================================


Test:
$ ./a.out -S projects
. (File Type: directory)
.. (File Type: directory)
.DS_Store (File Type: regular file)	(File Size: 6148)
project1 (File Type: directory)
     . (File Type: directory)
     .. (File Type: directory)
     README (File Type: regular file)	(File Size: 0)
     project1.docx (File Type: regular file)	(File Size: 0)
read.c (File Type: regular file)	(File Size: 0)
fread.c (File Type: regular file)	(File Size: 0)
project3 (File Type: directory)
     . (File Type: directory)
     .. (File Type: directory)
     project3.docx (File Type: regular file)	(File Size: 0)
     README (File Type: regular file)	(File Size: 0)
project4 (File Type: directory)
     . (File Type: directory)
     .. (File Type: directory)
     project4.docx (File Type: regular file)	(File Size: 0)
     README (File Type: regular file)	(File Size: 0)
project2 (File Type: directory)
     . (File Type: directory)
     .. (File Type: directory)
     project2.docx (File Type: regular file)	(File Size: 0)
     README (File Type: regular file)	(File Size: 0)
write.c (File Type: regular file)	(File Size: 0)
fwrite.c (File Type: regular file)	(File Size: 0)


===========================================================================================


$ ./a.out -S -s64 projects
. (File Type: directory)
.. (File Type: directory)
.DS_Store (File Type: regular file)	(File Size: 6148)
project1 (File Type: directory)
     . (File Type: directory)
     .. (File Type: directory)

===========================================================================================


$ ./a.out -S -f w projects
write.c (File Type: regular file)	(File Size: 0)
fwrite.c (File Type: regular file)	(File Size: 0)


===========================================================================================


$ ./a.out -S -t f projects
.DS_Store (File Type: regular file)	(File Size: 6148)
read.c (File Type: regular file)	(File Size: 0)
fread.c (File Type: regular file)	(File Size: 0)
write.c (File Type: regular file)	(File Size: 0)
fwrite.c (File Type: regular file)	(File Size: 0)


===========================================================================================


$ ./a.out -S -t d projects
. (File Type: directory)
.. (File Type: directory)
project1 (File Type: directory)
     . (File Type: directory)
     .. (File Type: directory)
project3 (File Type: directory)
     . (File Type: directory)
     .. (File Type: directory)
project4 (File Type: directory)
     . (File Type: directory)
     .. (File Type: directory)
project2 (File Type: directory)
     . (File Type: directory)
     .. (File Type: directory)


===========================================================================================



