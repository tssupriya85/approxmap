<h1>ApproxMAP : Sequence of sets </h1>
<h2> Exploratory Data Analysis of {A,B,D} {B} {B,C} </h2>


&lt;hr size="5"&gt;


<b>
Does your data look like {A,B,D} {B} {B,C} ?</b> <br>
Would you like to see what your data looks like?<br><br>
<table width='700' border='1'>
<tbody><tr><th align='center'> Some examples</th></tr>
<tr><td>life path analysis</td>
<td> {Graduation, Job1, Marriage} {Job1} {Job1, Birth} </td></tr>
<tr><td>welfare service analysis</td>
<td> {Foster Care, Medicaid, Foodstamp} {Medicaid} {Medicaid, TANF} </td></tr>
<tr><td>market basket analysis<br>
</td><td> {Bread, Milk, Jam} {Milk} {Milk, Banana} </td></tr>
</tbody></table>

<h3>Table 1: Basic Terms - sequence of sets</h3>
<table width='650' border='1'>
<blockquote><tbody><tr>
<blockquote><td width='120' valign='top'>Items I </td>
<td width='140' valign='top'>{A B C D} </td>
</blockquote></blockquote><blockquote><td width='390'> Let items be a set of literals<br>
I={i<sub>1</sub> i<sub>2</sub> i<sub>3</sub> ... i<sub>l</sub>}.<br>
</td></tr>
<blockquote><tr>
<blockquote><td width='' valign='top'>Itemsets s<sub>13 </sub></td>
<td width='' valign='top'>{B,C} </td>
</blockquote></blockquote><td>Then an itemset is a set of items (unordered list).</td></tr>
<blockquote><tr>
<blockquote><td valign='top'>Sequence seq<sub>1</sub> </td>
<td width='' valign='top'>{A,B,D} {B} {B,C} </td>
</blockquote></blockquote><td> And a sequence is an ordered list of  itemsets. </td></tr>
</tbody></table>
<br>
<p>Sequential pattern mining is an important data mining task with broad applications. We<br>
propose the theme of approximate sequential pattern mining roughly defined as<br>
identifying patterns approximately shared by many sequences. We present an<br>
efficient and effective algorithm, ApproxMAP (APPROXimate Multiple Alignment<br>
Pattern mining), to find maximal approximate sequential patterns from large<br>
databases. Our goal is to assist the data analyst in exploratory data analysis<br>
through organization and data reduction. The method works in three steps. </p>
<ol>
</blockquote><blockquote><li>First, similar sequences are grouped together using kNN clustering.<br>
</li><li>Then we organize and compress sequences within each cluster into weighted<br>
sequences using multiple alignment.<br>
</li><li>In the last step, the longest consensus pattern best fitting each<br>
cluster are generated from the weighted sequences. </li></ol>
<p>Our extensive experimental results on synthetic and real data show that<br>
ApproxMAP is very robust to noise and does well in mapping the high dimensional<br>
noisy data into approximate sequential patterns. </p>
<br>
<br>
<hr><br>
<br>
<br>
<b> An example </b>:<br>
Given below are 10 sequences lexically sorted. <br><br>
<ul>
<li> Step 1: ApproxMAP first divides the sequences into 2 clusters - <font color='red'>cluster 1</font> and <font color='blue'>cluster 2</font> (k was set to 2 for kNN clustering).<br><br>
<table width='700' border='1'>
<tbody><tr><td width='63' align='center'>ID  </td>
<td align='center'>Full Sequence Database lexically sorted<br>
</td>
<td width='52' align='center'>Cluster  </td>
<td width='52' align='center'>Lseq  </td>
<td width='52' align='center'>Len  </td>
</blockquote><blockquote></tr>
<tr>
<blockquote><td align='center'>seq<sub>1</sub>  </td>
<td width='81'> <font color='red'>{A}</font></td>
<td width='108'> <font color='red'>{B, C, Y}  </font></td>
<td width='84'> <font color='red'>{D}</font></td>
<td width='84'>   </td>
<td width='48'>    </td>
<td width='52' align='center'> <font color='red'>1  </font></td>
<td width='52' align='center'> 3  </td>
<td width='52' align='center'>5  </td>
</blockquote></tr>
<tr>
<blockquote><td width='63' align='center'>seq<sub>2</sub>  </td>
<td width='81'> <font color='red'>{A}  </font></td>
<td width='108'> <font color='red'>{X}  </font></td>
<td width='84'><font color='red'>{B, C}  </font></td>
<td width='84'> <font color='red'>{A, E}</font></td>
<td width='48'> <font color='red'>{Z}</font></td>
<td width='52' align='center'> <font color='red'>1  </font></td>
<td width='52' align='center'> 5  </td>
<td width='52' align='center'> 7  </td>
</blockquote></tr>
<tr>
<blockquote><td width='63' align='center'>seq<sub>3</sub>  </td>
<td width='81'> <font color='blue'>{A, I}</font></td>
<td width='108'> <font color='blue'>{Z}  </font></td>
<td width='84'> <font color='blue'>{K}  </font></td>
<td width='84'> <font color='blue'>{L, M}  </font></td>
<td width='48'>    </td>
<td width='52' align='center'> <font color='blue'>2  </font></td>
<td width='52' align='center'>4  </td>
<td width='52' align='center'>6  </td>
</blockquote></tr>
<tr>
<blockquote><td width='63' align='center'>seq<sub>4</sub>  </td>
<td width='81'> <font color='red'>{A, L}</font></td>
<td width='108'> <font color='red'>{D, E}</font></td>
<td width='84'>     </td>
<td width='84'>     </td>
<td width='84'>     </td>
<td width='52' align='center'> <font color='red'>1  </font></td>
<td width='52' align='center'>2  </td>
<td width='52' align='center'>4  </td>
</blockquote></tr>
<tr>
<blockquote><td width='63' align='center'>seq<sub>5</sub>  </td>
<td width='81'> <font color='blue'>{I, J}  </font></td>
<td width='108'> <font color='blue'>{B}  </font></td>
<td width='84'> <font color='blue'>{K}  </font></td>
<td width='84'> <font color='blue'>{L}  </font></td>
<td width='48'> <font color='blue'>     </font></td>
<td width='52' align='center'> <font color='blue'>2  </font></td>
<td width='52' align='center'>4  </td>
<td width='52' align='center'>5  </td>
</blockquote></tr>
<tr>
<blockquote><td width='63' align='center'>seq<sub>6</sub>  </td>
<td width='81'> <font color='blue'>{I, J}  </font></td>
<td width='108'> <font color='blue'>{L, M}  </font></td>
<td> <font color='blue'>     </font></td>
<td> <font color='blue'>     </font></td>
<td> <font color='blue'>     </font></td>
<td width='52' align='center'> <font color='blue'>2  </font></td>
<td width='52' align='center'>2  </td>
<td width='52' align='center'>5  </td>
</blockquote></tr>
<tr>
<blockquote><td width='63' align='center'>seq<sub>7</sub>  </td>
<td width='81'> <font color='blue'>{I, J}  </font></td>
<td width='108'> <font color='blue'>{K}  </font></td>
<td> <font color='blue'> {J, K} </font></td>
<td> <font color='blue'> {L} </font></td>
<td> <font color='blue'> {M} </font></td>
<td width='52' align='center'> <font color='blue'>2  </font></td>
<td width='52' align='center'>5 </td>
<td width='52' align='center'>7  </td>
</blockquote></tr>
<tr>
<blockquote><td width='63' align='center'>seq<sub>8</sub>  </td>
<td width='81'> <font color='blue'>{I, M}  </font></td>
<td width='108'> <font color='blue'>{K}  </font></td>
<td> <font color='blue'> {K, M} </font></td>
<td> <font color='blue'> {L, M} </font></td>
<td> <font color='blue'>     </font></td>
<td width='52' align='center'> <font color='blue'>2  </font></td>
<td width='52' align='center'>4 </td>
<td width='52' align='center'>7  </td>
</blockquote></tr>
<tr>
<blockquote><td width='63' align='center'>seq<sub>9</sub>  </td>
<td width='81'> <font color='blue'>{J}  </font></td>
<td width='108'> <font color='blue'>{K}  </font></td>
<td> <font color='blue'> {L, M} </font></td>
<td> <font color='blue'>     </font></td>
<td> <font color='blue'>     </font></td>
<td width='52' align='center'> <font color='blue'>2  </font></td>
<td width='52' align='center'>3 </td>
<td width='52' align='center'>4  </td>
</blockquote></tr>
<tr>
<blockquote><td width='63' align='center'>seq<sub>10</sub>  </td>
<td width='81'> <font color='blue'>{V}  </font></td>
<td width='108'> <font color='blue'>{K, W}  </font></td>
<td> <font color='blue'> {Z} </font></td>
<td> <font color='blue'>     </font></td>
<td> <font color='blue'>     </font></td>
<td width='52' align='center'> <font color='blue'>2  </font></td>
<td width='52' align='center'>3 </td>
<td width='52' align='center'>4  </td>
</blockquote></tr>
</tbody></table>
<br>
<li> Step 2: Then ApproxMAP aligns the sequences in each cluster and compresses<br>
each cluster into one weighted sequence as given in the following two tables.<br>
<br><br><li> Step 3: Finally, ApproxMAP generates a dominant pattern for each cluster<br>
using the weighted sequence as given in the following two tables.<br>
Cluster <a href='#sup'>strength</a> was set to 40%.  Thus, the dominant<br>
pattern is<br>
generated by selecting all items in the weighted<br>
sequence that have a weight more than 40% of the cluster. <br><br></blockquote>

<table width='700' border='1'>
<blockquote><tbody><tr>
<blockquote><td align='center'>Cluster 1<br>
(cluster strength = 40% = 2 sequences, Min_DB_sup = 1 sequence)  </td>
</blockquote></tr>
<tr>
<blockquote><td align='center'>seq<sub>1</sub>  </td>
<td width='81'> <font color='red'>{A}</font></td>
<td>   </td>
<td width='108'> <font color='red'>{B, C, Y}  </font></td>
<td width='84'> <font color='red'>{D}</font></td>
<td>   </td>
<td>   </td>
</blockquote></tr>
<tr>
<blockquote><td align='center'>seq<sub>4</sub>  </td>
<td width='81'> <font color='red'>{A, L}</font></td>
<td>   </td>
<td>   </td>
<td width='108'> <font color='red'>{D, E}</font></td>
<td>   </td>
<td>   </td>
</blockquote></tr>
<tr>
<blockquote><td align='center'>seq<sub>2</sub>  </td>
<td width='81'> <font color='red'>{A}  </font></td>
<td> <font color='red'>{X}  </font></td>
<td width='84'><font color='red'>{B, C}  </font></td>
<td width='84'> <font color='red'>{A, E}</font></td>
<td width='48'> <font color='red'>{Z}</font></td>
<td>   </td>
</blockquote></tr>
<tr>
<blockquote><td width='160' align='center'>Weighted sequence  </td>
<td>{A:3, L:1}:3  </td>
<td>{X:1}:1  </td>
<td>{B:2, C:2, Y:1}:2  </td>
<td>{A:1, D:2, E:2}:3  </td>
<td>{Z:1}:1  </td>
<td>3  </td>
</blockquote></tr>
<tr>
<blockquote><td align='center'> <i><b>Consensus Pattern (w>=2)</b></i>  </td>
<td> <font size='+2'><b>{A}</b></font></td>
<td>  </td>
<td><font size='+2'><b>{<font color='7f7f7f'>B</font>,<br>
<font color='7f7f7f'>C</font>} </b></font> </td>
<td><font size='+2'><b>{<font color='7f7f7f'>D</font>,<br>
<font color='7f7f7f'>E</font>}</b></font>  </td>
<td>  </td>
<td>  </td>
</blockquote></tr>
</tbody></table>
<br>
<font size='+2'><b>
<font color='000000'> Color scheme < 100:</font>
<font color='434343'> 85:</font>
<font color='767676'> 70:</font>
<font color='a9a9a9'> 50:</font>
<font color='c8c8c8'> 35:</font>
<font color='e1e1e1'> 20 </font>
<font color='000000'>   >;</font></b></font>
<br>
<br>
<table border='1'>
<tbody><tr>
<blockquote><td align='center'>Cluster 2 (cluster strength = 40% = 3<br>
sequences, Min_DB_sup = 1 sequence)</td>
</blockquote></tr>
<tr>
<blockquote><td align='center'>seq<sub>9</sub>  </td>
<td width='81'> <font color='blue'>{J}  </font></td>
<td> <font color='blue'>     </font></td>
<td width='108'> <font color='blue'>{K}  </font></td>
<td> <font color='blue'> {L, M} </font></td>
<td> <font color='blue'>     </font></td>
<td> <font color='blue'>     </font></td>
</blockquote></tr>
<tr>
<blockquote><td align='center'>seq<sub>5</sub>  </td>
<td width='81'> <font color='blue'>{I, J}  </font></td>
<td width='108'> <font color='blue'>{B}  </font></td>
<td width='84'> <font color='blue'>{K}  </font></td>
<td width='84'> <font color='blue'>{L}  </font></td>
<td> <font color='blue'>     </font></td>
<td> <font color='blue'>     </font></td>
</tr>
</blockquote><tr>
<blockquote><td align='center'>seq<sub>3</sub>  </td>
<td width='81'> <font color='blue'>{A, I}</font></td>
<td width='108'> <font color='blue'>{Z}  </font></td>
<td width='84'> <font color='blue'>{K}  </font></td>
<td width='84'> <font color='blue'>{L, M}  </font></td>
<td> <font color='blue'>     </font></td>
<td> <font color='blue'>     </font></td>
</blockquote></tr>
<tr>
<blockquote><td align='center'>seq<sub>7</sub>  </td>
<td width='81'> <font color='blue'>{I, J}  </font></td>
<td width='108'> <font color='blue'>{K}  </font></td>
<td> <font color='blue'> {J, K} </font></td>
<td> <font color='blue'> {L} </font></td>
<td> <font color='blue'> {M} </font></td>
<td> <font color='blue'>     </font></td>
</blockquote></tr>
<tr>
<blockquote><td align='center'>seq<sub>8</sub>  </td>
<td width='81'> <font color='blue'>{I, M}  </font></td>
<td width='108'> <font color='blue'>{K}  </font></td>
<td> <font color='blue'> {K, M} </font></td>
<td> <font color='blue'> {L, M} </font></td>
<td> <font color='blue'>     </font></td>
<td> <font color='blue'>     </font></td>
</blockquote></tr>
<tr>
<blockquote><td align='center'>seq<sub>6</sub>  </td>
<td width='81'> <font color='blue'>{I, J}  </font></td>
<td> <font color='blue'>     </font></td>
<td> <font color='blue'>     </font></td>
<td> <font color='blue'>{L, M}  </font></td>
<td> <font color='blue'>     </font></td>
<td> <font color='blue'>     </font></td>
</blockquote></tr>
<tr>
<blockquote><td align='center'>seq<sub>10</sub>  </td>
<td> <font color='blue'>     </font></td>
<td width='81'> <font color='blue'>{V}  </font></td>
<td width='108'> <font color='blue'>{K, W}  </font></td>
<td> <font color='blue'>     </font></td>
<td> <font color='blue'> {Z} </font></td>
<td> <font color='blue'>     </font></td>
</blockquote></tr>
<tr>
<blockquote><td align='center'>Weighted seq  </td>
<td>{A:1,I:5,J:4,M:1}:6  </td>
<td>{B:1,K:2,V:1,Z:1}:5  </td>
<td>{J:1,K:6,M:1,W:1}:6  </td>
<td>{L:6,M:4}:6  </td>
<td>{M:1,Z:1}:2  </td>
<td> 7  </td>
</blockquote></tr>
<tr>
</tr><tr>
<blockquote><td width='166' align='center'> <i><b>Consensus Pat(w>=3)</b></i>  </td>
<td> <font size='+2'><b>{<font color='717171'>I</font>,<br>
<font color='989898'>J</font>}</b></font></td>
<td>  </td>
<td> <font size='+2'><b>{<font color='404040'>K</font>} </b></font>  </td>
<td><font size='+2'><b>{<font color='404040'>L</font>,<br>
<font color='989898'>M</font>}</b></font>  </td>
<td>  </td>
<td>  </td>
</blockquote></tr>
<blockquote><tr><td width='166' align='center'> <i><b>Consensus Var(w>=2)</b></i>  </td>
<td> <font size='+2'><b>{<font color='717171'>I</font>,<br>
<font color='989898'>J</font>}</b></font></td>
<td>  <font size='+2'><b>{<font color='d3d3d3'> K</font>} </b></font>  </td>
<td> <font size='+2'><b>{<font color='404040'>K</font>} </b></font>  </td>
<td><font size='+2'><b>{<font color='404040'>L</font>,<br>
<font color='989898'>M</font>}</b></font>  </td>
<td>  </td>
<td>  </td></blockquote></blockquote>

<blockquote></tr>
</tbody></table>
<br>
<ul>
<li> Which would you prefer to look at, the first table of 10 sequences<br>
lexically sorted or the grouped and aligned sequences in the next two<br>
tables?<br>
</li><li> Imagine what would happen in real applications where you have<br>
many more sequences (N >> 100).  If you were to glance through the aligned sequences then studied the dominant patterns generated for each cluster, wouldn't you be able to get a good understanding of what your data looked like?<br>
</li><li> If you are interested to learn more about ApproxMAP email us at<br>
approxmap@unc.edu  This webpage is still under construction.<br>
</li><li> How can you get software that does ApproxMAP?  We have a not-so user<br>
friendly software.  We will consider running the analysis for you and<br>
we are open to discussing other possibilities. Email us at<br>
approxmap@unc.edu<br>
</li></ul>
<br>
<br>
<hr><br>
<br>
<br>
<b>Glossary</b><br><br>
<ul>
<li><b><a>Weighted sequences</a></b><a> are an effective method to compress a whole group of aligned sequences into one sequence. </a>
<br><br>
<table width='600' border='1'>
<tbody>
<tr>
<th valign='top'><b>An example of weighted sequences</b> </th></tr>
<tr>
<td width='200' align='center' valign='top'>seq<sub>1</sub> </td>
<td width='100' valign='top'>{A} </td>
<td width='100' valign='top'>{B} </td>
<td width='100' valign='top'>{C, D} </td>
<td width='100' valign='top'></td></tr>
<tr>
<td align='center' valign='top'>seq<sub>2 </sub></td>
<td valign='top'>{A} </td>
<td valign='top'>   </td>
<td valign='top'>{C} </td>
<td valign='top'></td></tr>
<tr>
<td align='center' valign='top'>Weighted sequence </td>
<td valign='top'>{A:2}:2 </td>
<td valign='top'>{B:1}:1 </td>
<td valign='top'>{C:2, D:1}:2 </td>
<td valign='top'>2<br>
</td></tr></tbody></table></blockquote>

<p> A weighted itemset is defined as an itemset that has a weight associated with each item in the itemset as well as the itemset itself. It is denoted as ws<sub>j</sub> ={i<sub>1</sub>:w<sub>1</sub>, i<sub>2</sub>:w<sub>2</sub>, ... , i<sub>m</sub>:w<sub>m</sub>}:w<sub>j</sub>. Then a weighted sequence is an ordered list of weighted itemsets paired with a separate weight for the whole sequence. The table above show the aligned sequences and its weighted sequence. The weight associated with the sequence is the total number of sequences, N, in the group. The weight associated with the itemset s<sub>j</sub>, represents how many sequences have a non-empty itemset in position j. And the weight associated with each item i<sub>k</sub> in itemset s<sub>j</sub> represents the total number of the item i<sub>k</sub> present in all itemsets in position j.<br>
<br>
<li><b><a>Consensus Patterns</a></b><a> : similar to consensus strings in computational biology literature, it is the underlying sequential pattern in a group of similar sequences. In social sciences, it is also called the ideal sequence, a hypothetical sequence that best captures the patterns among all the sequences in a cluster.  Unlike optimal matching ApproxMAP generates the dominant pattern automatically<br>
given a user input - the cluster strength.<br>
<br>
<li><a><b></b></a><b><a>Strength (i, j)</a></b><a> : the number of occurances of item i in position j in a group. Thus, cluster strength means how many times an item i occured in the cluster at position j. Strength can be specified as a % of the group (e.g. 40% of the cluster) or as an absolute number (e.g. 10 sequences). <a> <br>
<br>
<hr size="5"><br>
<br>
<br>
<br>
<b>Copyright (C) 2010 Hye-Chung Kum</b>