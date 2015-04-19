# Steps to install cygwin: #

1. Go to the website : http://www.cygwin.com/
<br><br><br>
2. Click on the following image in the website<br>
<br>
<img src='http://www.unc.edu/~kum/approxmap/images/i_1.jpg' />
<br>
and download cygwin installation file.<br>
<br>

3. Double click on setup file to install cygwin.<br>
<br>

<img src='http://www.unc.edu/~kum/approxmap/images/i_2.jpg' />

4. Click Next.<br>
<br>
<br>

5. Select: Install from internet and click next<br>
<br>
<img src='http://www.unc.edu/~kum/approxmap/images/i_3.jpg' />

6. Select a known location (Ex: c:\cygwin) and then click next<br>
<br>
<img src='http://www.unc.edu/~kum/approxmap/images/i_4.jpg' />
<br>

7. Click next<br>
<br>

<img src='http://www.unc.edu/~kum/approxmap/images/i_5.jpg' />

8. Click next<br>
<br>

<img src='http://www.unc.edu/~kum/approxmap/images/i_6.jpg' />

9. Click next and wait<br>
<br>

<img src='http://www.unc.edu/~kum/approxmap/images/i_7.jpg' />
<br>

10. You will get the following error if it is a first time setup -> Click OK<br>
<br>

<img src='http://www.unc.edu/~kum/approxmap/images/i_8.jpg' />


11. In the search box type GCC<br>
<br>

<img src='http://www.unc.edu/~kum/approxmap/images/i_9.jpg' />


12. Search GCC:<br>
Click on skip once<br>
Select:  GCC-core, GCC-G++ compiler<br>
<br>
<br>

<img src='http://www.unc.edu/~kum/approxmap/images/i_10.jpg' />

Search again for “make” and click on skip once.<br>
Select: make, as shown in the figure below.<br>
<br>
<br>

<img src='http://www.unc.edu/~kum/approxmap/images/i_11.jpg' />


You may want to install a commonly used unix editor such as “emacs” or “vim”. So search them and install them appropriately.<br>
<br>
13. Click next this will install the package. Downloading and installation is taking place now so this step will take some time to perform.<br>
<br>
<br>

<img src='http://www.unc.edu/~kum/approxmap/images/i_12.jpg' />

14. After installation click finish to create a shortcut on your desktop. If you are not familiar with Unix, the basic commands you need to know for using ApproxMAP is given in the wiki section of the website. <a href='http://code.google.com/p/approxmap/'>http://code.google.com/p/approxmap/</a>

<br>

<img src='http://www.unc.edu/~kum/approxmap/images/i_13.jpg' />

<h1>Compiling the program ApproxMAP</h1>

15. Double Click on cygwin icon on desktop and open cygwin.<br>
<br>
<br>

<img src='http://www.unc.edu/~kum/approxmap/images/i_14.jpg' />

16. Download approxmap.zip from download page.<br>
If you have downloaded approxmap.tar.gz to extract the files follow the instructions which are given in the bottom of this document.<br>
<br>
17. Copy and paste approxmap.zip at C:\cygwin\home\user_name. If you want to use a different location, see instructions on setting your home directory in cygwin given in the appendix.<br>
<br>
<br>
18. Extract the files at the same location<br>
<br>
19. After extraction type<br>
cd approxmap<br>
To enter into the approxmap folder.<br>
<br>
20. Type ls to list the files in the folder<br>
<br>

<img src='http://www.unc.edu/~kum/approxmap/images/i_15.jpg' />

21. Type “make approx” and press enter to compile<br>
<br>

<img src='http://www.unc.edu/~kum/approxmap/images/i_16.jpg' />

<b>NOTE</b>: You might get a few warning messages about depreciated values during compilation.  You may ignore them.<br>
<br>
22. Now approxmap has been compiled. To view the files type ls<br>
<br>

<img src='http://www.unc.edu/~kum/approxmap/images/i_17.jpg' />

23. approx.exe is the file for execution.  If you type ./approx.exe you will get a simple syntax on how to use the program. Below are more detailed explanations.<br>
<br>
<h1>Using ApproxMAP</h1>

24. Now to run ApproxMAP move into the directory (cd dir) which has the data you created.  We will use a tiny example file that is included in the download to demonstrate how to use ApproxMAP.  Go into the example folder, where you should have the “tiny.data” example data file. For the format of the data file, see the User Manual.  The command to type in cygwin:<br>
cd example<br>
<br>
25. Syntax to execute ApproxMAP<br>
<br>
../approx.exe fn -data kNN<br>
<br>
approx.exe: the executable program<br>
fn : the file name of your data set excluding the extension .data (fn.data)<br>
-data : indicates the input file is of type data and is required<br>
kNN : specifies the number of k nearest neighbors (kNN) in the clustering algorithm<br>
<br>
So if you wanted to run the program on the sample data file tiny.data using kNN=2, then you would type if the following command.<br>
../approx.exe tiny -data 2<br>
<br>
<b>NOTE</b>: If you run into segmentation errors when you run the code, it is likely that you did not properly installed cygwin.  Try to reinstall cygwin (follow step 1 to 14).<br>
<br>
26. Once the code has run we get 3 files namely:<br>
<br>
fnkNN0.html, fnkNN0.cprof, fnkNN0.prof<br>
<br>
So in our example you would get tiny20.html, tiny20.cprof, tiny20.prof<br>
<br>
Here the file name is fn followed by the kNN in the clustering algorithm, 2 in our example, then 0 (internal book keeping), and the different extensions (html, prof, cprof).<br>
<br>
27. Load in the <b>.html file in our browser (double click) and you will see the number of clusters and the main patterns in each cluster.</b>

To know about these files in more detail look at the user manual.<br>
<br>
<br>
<br>
<h1>APPENDIX</h1>

Extracting “approxmap.tar.gz” files.<br>
<br>
28. Download the approxmap.tar.gz<br>
<br>
29. Paste the downloaded file in the following location.<br>
<blockquote>C:\cygwin\home\user_name<br>
30. In cygwin type the following syntax<br>
tar -zxvf extractme.tar.gz</blockquote>

Setting your home directory to a particular location in cygwin<br>
Optional. Setup your home directory for cygwin so you can easily access your files from cygwin.  If this is not set, cygwin will automatically create a file C:\cygwin\home\user_name as your home directory (This plays a similar role to my Documents location in windows. It will be the default directory you start your cygwin in.) You can also set a user environment variable ‘home’ to the directory you want to use as your default data directory for cygwin. In Win XP:<br>
<br>
My Computer<br>
right click Properties<br>
Advanced tab<br>
Environment Variables button<br>
In User variables, click New button<br>
Variable name : HOME<br>
Variable value : location of the directory you want to use as home<br>
For example, c:\ Documents and Settings\userid<br>
<br>
<br>
<br>
<hr size="5"><br>
<br>
<br>
<br>
<b>Copyright (C) 2010 Hye-Chung Kum</b>