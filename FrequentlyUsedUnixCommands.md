| **The Command** | **What it Means** | **Example** | **Output** |
|:----------------|:------------------|:------------|:-----------|
|man command|	"Manual." This displays the help pages for a command. Hit the space bar to scroll through each screen, and hit "q" to quit.| man ls|	Displays help for the command "ls". |
|ls|	"List." Displays the contents of your current directory (folder).| ls |A list of file names.|
|ls -l|"List." The "-l" means "list in long format." Information such as the time a file was last modified is displayed.|ls -l|A list of file names with info about each file is displayed.|
|cd dirname|"Change Directory." Changes your current directory (folder) to dirname.|cd mySasProgs|	You are now in folder "mySasProgs."|
|pwd|	"Print Working Directory." Prints the name of the directory (folder) you are in.|	pwd|	Displays the name of a folder.|
|cd ..|"Change Directory." Makes your current directory move up one directory.|cd ..|If you were in folder "mySasProgs/Prog1/", after you enter "cd ..", you will be in "mySasProgs/".|
|mkdir dirname|"Make Directory." Makes a new directory (folder) called dirname.|	mkdir sasPrograms|No output, but a directory called "sasPrograms" has been created.|
|cp source destination	|"Copy". Copies source to destination (-p : perserve timestamp).|cp program1.sas program1Backup.sas|Makes a copy of "program1.sas" and calls it "program1Backup.sas"|
|mv source destination|"Move". Moves source to destination. You can also think of this command as the "Rename" command.|mv program1.sas sampleProgram.sas|Renames "program1.sas" to "sampleProgram.sas"|
|rm filename|"Remove." Deletes filename.|rm testProgram.sas|Removes testProgram.sas|
|rmdir dirname|"Remove Directory." Deletes the directory (folder) dirname.|rm temp|Removes the directory called "temp."|
|tar czvf destination.tar.gz sourcefolder/|"Creating a tape Archive" Create tape archives and add files | tar czvf myfolder.tar.gz abcfolder/ | Creates a tape archive (zip) a folder at your current directory say "abcfolder" |
|tar -zxvf source.tar.gz|"Extracting Files from tape Archive" | tar -zxvf extractme.tar.gz | Extracts files from tape archive (zip) to your current directory |
|diff source1 source2|"differences between the files" | diff 1.txt 2.txt | Difference between 1.txt and 2.txt. Diff change notation includes 2 numbers and a character between them. Characters tell you what kind of change was discovered: d – a line was deleted, c – a line was changed, a – a line was added, Number to the left of the character gives you the line number in the original (first) file, and the number to the right of the character tells you the line number in the second file used in comparison. |



&lt;hr size="5"&gt;



**Copyright (C) 2010 Hye-Chung Kum**




&lt;hr size="5"&gt;


Copyright (C) 2010 Hye-Chung Kum