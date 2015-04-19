# Example: #
This example has a very small dataset and is used to explain the output
files.  It is too small to have any meaningful results.

<u> <b>Step1:</b> </u> Generate a data file for you sequences:

This example is in reference to the
[HANDOUT](http://www.unc.edu/~kum/approxMAP/papers/kum_handout.pdf)

The example sequence is as shown below.
<br>
<img src='http://www.unc.edu/~kum/approxmap/images/um_1.jpg' />
<br>
First convert the characters in the sequence to numbers (ex: A = 1, B = 2 … )<br>
Then the data file should be in the following format for the first sequence.<br>
1 1 1<br>
1 2 2<br>
1 2 3<br>
1 2 25<br>
1 3 4<br>
Here, First column represents the sequence number (seq1)<br>
Second column represents the itemset number ((A) or (B,C,Y) or (D)<br>
Third column represents the character number (A=1, B=2, C=3..ect)<br>
<br>
Write all the sequences in a single data file as shown in the tiny.data file.<br>
<br>
<br>
<u> <b>Step2:</b> </u>../approx.exe tiny –data 2<br>
<br>
As soon as you run the code, we can see the following message. Check that your sequences are being processed in the program properly by checking the first 10 sequences printed.  If it is not, check the format of your data file.<br>
<br>
<img src='http://www.unc.edu/~kum/approxmap/images/um_1.jpg' />
<br>
Syntax for ApproxMAP usage:<br>
approx.exe fn -data kNN<br>
<br>
<table><thead><th> <b>Function</b> </th><th> <b>Explanation</b> </th></thead><tbody>
<tr><td>fn</td><td>represents the input file (.data format)</td></tr>
<tr><td>-data</td><td>specify the program that the input file is of type data</td></tr>
<tr><td>kNN</td><td>specify the number of k nearest neighbors in the clustering algorithm</td></tr></tbody></table>


<b>Output files:</b>

<b>NOTE: You may notice that the file name has changed from “file_name” to “file_nameN0” where N is the number of clusters in kNN algorithm.</b>

<u> <b>Step3:</b> </u>Open the example folder.<br>
<br>
Once the code has run we get 3 files in the same folder namely: <b>.html</b>.prof <b>.cprof</b>

<b>NOTE:</b> <code>*</code>.html is the primary file giving the overview of the results.  Load this file into a browser (double click).  For more details about the results, you can open <code>*</code>.prof and <code>*</code>.cprof flies using notepad or any other editor.<br>
<br>
<code>*</code>.html – Displaying all the clusters using color schemes<br>
Color scheme <100: 85: 70: 50: 35: 20 > represents the weight of an item in the<br>
sequences in terms of percentages, where 100 represents the maximum strength and 20 the minimum.<br>
<br>
The first line says that 50% pattern consensus sequences are present and<br>
20% weighted sequences are present.<br>
In the second line cluster 0 and 1 are printed in a color scheme which<br>
shows weighted sequence in terms of percentages.<br>
<br>
<b>Example:</b>

<font color='000000'> Cluster Support= </font>
<font color='000000'> 50</font>
<font color='000000'> % :</font>
<font color='000000'> 20</font>
<font color='000000'> % Database Support Min : Max= </font>
<font color='000000'> 10</font>
<font color='000000'>  seq:</font>
<font color='000000'> 10</font>
<font color='000000'> %</font>
<font color='000000'> noise:type</font>
<br>
<br>
<BR><br>
<br>
<br>
<font color='a9a9a9'> cluster=0 size=3</font>
<font color='000000'>   =<100:</font>
<font color='434343'> 85:</font>
<font color='767676'> 70:</font>
<font color='a9a9a9'> 50:</font>
<font color='c8c8c8'> 35:</font>
<font color='e1e1e1'> 20></font>

<br>
<br>
<BR><br>
<br>
<br>
<font color='000000'> <u><b>PATTERN:=0</b></u>
<br>
<br>
<BR><br>
<br>
<br>
<font color='000000'> {</font>
<font color='000000'> 1</font>
<font color='cbcbcb'> 12</font>
<font color='000000'> }</font>
<font color='000000'> {</font>
<font color='cbcbcb'> 24</font>
<font color='000000'> }</font>
<font color='000000'> {</font>
<font color='7f7f7f'> 2</font>
<font color='7f7f7f'> 3</font>
<font color='cbcbcb'> 25</font>
<font color='000000'> }</font>
<font color='000000'> {</font>
<font color='cbcbcb'> 1</font>
<font color='7f7f7f'> 4</font>
<font color='7f7f7f'> 5</font>
<font color='000000'> }</font>
<font color='000000'> {</font>
<font color='cbcbcb'> 26</font>
<font color='000000'> }</font>
<br>
<br>
<BR><br>
<br>
<br>
<font color='a9a9a9'> cluster=1 size=7</font>
<font color='000000'>   =<100:</font>
<font color='434343'> 85:</font>
<font color='767676'> 70:</font>
<font color='a9a9a9'> 50:</font>
<font color='c8c8c8'> 35:</font>
<font color='e1e1e1'> 20></font>
<br>
<br>
<BR><br>
<br>
<br>
<font color='000000'> <u><b>PATTERN:=0</b></u>
<br>
<br>
<BR><br>
<br>
<br>
<font color='000000'> {</font>
<font color='eaeaea'> 1</font>
<font color='717171'> 9</font>
<font color='989898'> 10</font>
<font color='eaeaea'> 13</font>
<font color='000000'> }</font>
<font color='000000'> {</font>
<font color='eaeaea'> 2</font>
<font color='d3d3d3'> 11</font>
<font color='eaeaea'> 22</font>
<font color='eaeaea'> 26</font>
<font color='000000'> }</font>
<font color='000000'> {</font>
<font color='eaeaea'> 10</font>
<font color='404040'> 11</font>
<font color='eaeaea'> 13</font>
<font color='eaeaea'> 23</font>
<font color='000000'> }</font>
<font color='000000'> {</font>
<font color='404040'> 12</font>
<font color='989898'> 13</font>
<font color='000000'> }</font>
<font color='000000'> {</font>
<font color='eaeaea'> 13</font>
<font color='eaeaea'> 26</font>
<font color='000000'> }</font>
<br>
<br>
<BR><br>
<br>
<br>
<font color='000000'> TOTAL LEN=</font>
<font color='000000'> 0</font>


To understand other files look into appendix for further details.<br>
<br>
<h1>Appendix:</h1>

<code>*</code>.cprof – the consensus profile file has the consensus patterns<br>
<br>
Output: tiny20.cprof<br>
<br>
In this file the first line represent cluster number and size of the cluster.<br>
From the second line to the next cluster the lines represent the weighted sequences, each line being an weighted itemset in the consensus pattern. The first number in () is the item number, followed by the weight of the item in the pattern.  Each line as the weighted itemset in {} followed by the weight for the itemset.  Thus, below :3 at the end of line one represents the itemset weight for the consensus pattern indicating that all 3 sequences in the first cluster have an itemset aligned to this position.  Furthermore, (1:3) below represents that there are 3 A’s in the first itemset in the consensus pattern.  There is also one L (12:1) in the same itemset.<br>
<br>
<b>Example</b> <br>
cluster0;Fsize=3<br>
{(1:3),(12:1),}:3<br>
{(24:1),}:1<br>
{(2:2),(3:2),(25:1),}:2<br>
{(1:1),(4:2),(5:2),}:3<br>
{(26:1),}:1<br>
cluster1;Fsize=7<br>
{(1:1),(9:5),(10:4),(13:1),}:6<br>
{(2:1),(11:2),(22:1),(26:1),}:5<br>
{(10:1),(11:6),(13:1),(23:1),}:6<br>
{(12:6),(13:4),}:6<br>
{(13:1),(26:1),}:2<br>


<code>*</code>.prof – the profile file give the actual alignment and sequences in each cluster<br>
<br>
<b>Example:</b> <br>
0;s=3;1;{1,12,} {24,} {2,3,25,} {1,4,5,} {26,} ;5;10<br>
cluster0;size=3;1;{1,12,} {24,} {2,3,25,} {1,4,5,} {26,}<br>
cluster0;precent;1;{100,33,} {33,} {66,66,33,} {33,66,66,} {33,} <br>
0;1;1;{1,} {} {2,3,25,} {4,} {} <br>
1;4;1;{1,12,} {} {} {4,5,} {} <br>
3;2;1;{1,} {24,} {2,3,} {1,5,} {26,} <br>
1;s=7;1;{1,9,10,13,} {2,11,22,26,} {10,11,13,23,} {12,13,} {13,26,} ;5;16<br>
cluster1;size=7;1;{9,10,} {11,} {11,} {12,13,} {} <br>
cluster1;precent;1;{71,57,(2)} {28,(3)} {85,(3)} {85,57,} {(2)} <br>
8;9;1;{10,} {} {11,} {12,13,} {} <br>
4;5;1;{9,10,} {2,} {11,} {12,} {} <br>
2;3;1;{1,9,} {26,} {11,} {12,13,} {} <br>
6;7;1;{9,10,} {11,} {10,11,} {12,} {13,} <br>
7;8;1;{9,13,} {11,} {11,13,} {12,13,} {} <br>
5;6;1;{9,10,} {} {} {12,13,} {} <br>
9;10;1;{} {22,} {11,23,} {} {26,}<br>

<u>Line 1:</u>
The first number (0) represents id of the cluster<br>
S=3 shows the size of cluster<br>
The number 1 after S=3 is a system value, you can ignore it.<br>
After which the weighted sequence without weights are printed.<br>
The last two numbers 5 and 11 represents the total number of sets and elements in the pattern.<br>
<br>
<u>Line 2 & 3: </u>
Variation consensus sequences.<br>
Line 2 is the consensus sequence, and line 3 is the weight of each item in percentage.<br>
<br>
<u>Line 4:</u>
Weights in percentages and alignment sequence for each cluster.<br>
0;1;1;{1,} {} {2,3,25,} {4,} {}  shows that it is<br>
0 – Program defined sequence number (internal, can ignore)<br>
1 – User defined sequence 1<br>
1 – Frequencies of the sequence in the data set.  If you have more than one sequence that are identical, than ApproxMAP will combine them and use frequencies to keep track internally.<br>
0;1;1;{1,} {} {2,3,25,} {4,} {} --- The aligned sequence in the clusters.  So this represents (A)(INDEL)(B,C,Y,)(D) (INDEL) below in seq1.<br>
The null brackets represent positions where INDEL occurred to align this sequence to the sequences in the rest of the cluster.<br>
<br><br>
<img src='http://www.unc.edu/~kum/approxmap/images/um_1.jpg' />
<br>
<br>
<hr size="5"><br>
<br>
<br>
<br>
<b>Copyright (C) 2010 Hye-Chung Kum</b>