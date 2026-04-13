# API参考

## 接口列表

KVecTurbo提供的接口如[**表 1** KVecTurbo提供的接口](#KVecTurbo提供的接口)所示。

**表 1** KVecTurbo提供的接口<a id="KVecTurbo提供的接口"></a>

<a name="table1194910128449"></a>
<table><thead align="left"><tr id="row99491812134412"><th class="cellrowborder" valign="top" width="31.25%" id="mcps1.2.3.1.1"><p id="p1794951224415"><a name="p1794951224415"></a><a name="p1794951224415"></a>接口名称</p>
</th>
<th class="cellrowborder" valign="top" width="68.75%" id="mcps1.2.3.1.2"><p id="p6949612124415"><a name="p6949612124415"></a><a name="p6949612124415"></a>接口作用</p>
</th>
</tr>
</thead>
<tbody><tr id="row712018285575"><td class="cellrowborder" valign="top" width="31.25%" headers="mcps1.2.3.1.1 "><p id="p12121102835714"><a name="p12121102835714"></a><a name="p12121102835714"></a>ComputePQTable</p>
</td>
<td class="cellrowborder" valign="top" width="68.75%" headers="mcps1.2.3.1.2 "><p id="p111217289571"><a name="p111217289571"></a><a name="p111217289571"></a>计算PQ码本。</p>
</td>
</tr>
<tr id="row119491112174414"><td class="cellrowborder" valign="top" width="31.25%" headers="mcps1.2.3.1.1 "><p id="p539219519167"><a name="p539219519167"></a><a name="p539219519167"></a>ComputeVectorPQCode</p>
</td>
<td class="cellrowborder" valign="top" width="68.75%" headers="mcps1.2.3.1.2 "><p id="p617774433819"><a name="p617774433819"></a><a name="p617774433819"></a>根据PQ码本，量化输入向量。</p>
</td>
</tr>
<tr id="row9949131219443"><td class="cellrowborder" valign="top" width="31.25%" headers="mcps1.2.3.1.1 "><p id="p1094921294415"><a name="p1094921294415"></a><a name="p1094921294415"></a>GetPQDistanceTableSdc</p>
</td>
<td class="cellrowborder" valign="top" width="68.75%" headers="mcps1.2.3.1.2 "><p id="p1794941284418"><a name="p1794941284418"></a><a name="p1794941284418"></a>计算PQ SDC距离表，即计算各个子空间内聚类中心之间的距离。</p>
</td>
</tr>
<tr id="row1594913120443"><td class="cellrowborder" valign="top" width="31.25%" headers="mcps1.2.3.1.1 "><p id="p472151416393"><a name="p472151416393"></a><a name="p472151416393"></a>GetPQDistanceTableAdc</p>
</td>
<td class="cellrowborder" valign="top" width="68.75%" headers="mcps1.2.3.1.2 "><p id="p1509193871710"><a name="p1509193871710"></a><a name="p1509193871710"></a>计算PQ ADC距离表，即计算查询向量和各个子空间内聚类中心的距离。</p>
</td>
</tr>
<tr id="row6949131274416"><td class="cellrowborder" valign="top" width="31.25%" headers="mcps1.2.3.1.1 "><p id="p81502298399"><a name="p81502298399"></a><a name="p81502298399"></a>GetPQDistance</p>
</td>
<td class="cellrowborder" valign="top" width="68.75%" headers="mcps1.2.3.1.2 "><p id="p31521029163914"><a name="p31521029163914"></a><a name="p31521029163914"></a>计算PQ ADC或SDC距离。若querycode == NULL，计算的是ADC距离；若querycode != NULL，计算的是SDC距离。</p>
</td>
</tr>
</tbody>
</table>

## 结构体说明

KVecTurbo提供的接口所使用参数涉及“VectorArray“和“PQParams“两类结构体，详细参数描述如[**表 1** 结构体VectorArray字段描述](#结构体VectorArray字段描述)和[**表 2** 结构体PQParams字段描述](#结构体PQParams字段描述)所示。

**表 1** 结构体VectorArray字段描述<a id="结构体VectorArray字段描述"></a>

<a name="table1646711617442"></a>
<table><thead align="left"><tr id="row846751612442"><th class="cellrowborder" valign="top" width="16.27%" id="mcps1.2.5.1.1"><p id="p81762043154713"><a name="p81762043154713"></a><a name="p81762043154713"></a>字段名称</p>
</th>
<th class="cellrowborder" valign="top" width="21.82%" id="mcps1.2.5.1.2"><p id="p4377125320521"><a name="p4377125320521"></a><a name="p4377125320521"></a><strong id="b1137765315529"><a name="b1137765315529"></a><a name="b1137765315529"></a>描述</strong></p>
</th>
<th class="cellrowborder" valign="top" width="18.88%" id="mcps1.2.5.1.3"><p id="p335712558441"><a name="p335712558441"></a><a name="p335712558441"></a><strong id="b153571755154417"><a name="b153571755154417"></a><a name="b153571755154417"></a>数据类型</strong></p>
</th>
<th class="cellrowborder" valign="top" width="43.03%" id="mcps1.2.5.1.4"><p id="p8357955164412"><a name="p8357955164412"></a><a name="p8357955164412"></a><strong id="b335775510441"><a name="b335775510441"></a><a name="b335775510441"></a>取值范围</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row18468216154410"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p8902349194711"><a name="p8902349194711"></a><a name="p8902349194711"></a>maxLen</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p4377115320525"><a name="p4377115320525"></a><a name="p4377115320525"></a>向量最大个数。</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p784815918455"><a name="p784815918455"></a><a name="p784815918455"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p484829144516"><a name="p484829144516"></a><a name="p484829144516"></a>若取值过大，可能因系统内存资源限制导致内存分配操作失败。</p>
</td>
</tr>
<tr id="row4356161812514"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p1236742011517"><a name="p1236742011517"></a><a name="p1236742011517"></a>length</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p1936720201356"><a name="p1936720201356"></a><a name="p1936720201356"></a>向量个数。</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p123673202050"><a name="p123673202050"></a><a name="p123673202050"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p1836710201655"><a name="p1836710201655"></a><a name="p1836710201655"></a>[1,maxLen]，其中<span class="parmname" id="parmname152384663517"><a name="parmname152384663517"></a><a name="parmname152384663517"></a>“maxLen”</span>是结构体<span class="parmname" id="parmname18437102572918"><a name="parmname18437102572918"></a><a name="parmname18437102572918"></a>“VectorArray”</span>中的字段，表示向量最大个数。</p>
</td>
</tr>
<tr id="row746811684410"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p159021849104714"><a name="p159021849104714"></a><a name="p159021849104714"></a>dim</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p12377153155215"><a name="p12377153155215"></a><a name="p12377153155215"></a>向量维度。</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p48488911459"><a name="p48488911459"></a><a name="p48488911459"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p08481993451"><a name="p08481993451"></a><a name="p08481993451"></a>[1,2000]</p>
</td>
</tr>
<tr id="row84681167446"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p1190210496473"><a name="p1190210496473"></a><a name="p1190210496473"></a>itemSize</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p2377753175214"><a name="p2377753175214"></a><a name="p2377753175214"></a>单个向量长度。</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p1784811934515"><a name="p1784811934515"></a><a name="p1784811934515"></a>size_t</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p16848139174518"><a name="p16848139174518"></a><a name="p16848139174518"></a>限制非0。</p>
</td>
</tr>
<tr id="row11468101614449"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p1290213494474"><a name="p1290213494474"></a><a name="p1290213494474"></a>items</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p163771553175210"><a name="p163771553175210"></a><a name="p163771553175210"></a>length个向量首地址。</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p28481299458"><a name="p28481299458"></a><a name="p28481299458"></a>char*</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p13848119154518"><a name="p13848119154518"></a><a name="p13848119154518"></a>限制非空。</p>
</td>
</tr>
</tbody>
</table>

**表 2** 结构体PQParams字段描述<a id="结构体PQParams字段描述"></a>

<a name="table11706934103516"></a>
<table><thead align="left"><tr id="row11414124012358"><th class="cellrowborder" valign="top" width="16.27%" id="mcps1.2.5.1.1"><p id="p82251946143516"><a name="p82251946143516"></a><a name="p82251946143516"></a>字段名称</p>
</th>
<th class="cellrowborder" valign="top" width="21.82%" id="mcps1.2.5.1.2"><p id="p102251046193511"><a name="p102251046193511"></a><a name="p102251046193511"></a><strong id="b9225194613512"><a name="b9225194613512"></a><a name="b9225194613512"></a>描述</strong></p>
</th>
<th class="cellrowborder" valign="top" width="18.88%" id="mcps1.2.5.1.3"><p id="p16225194616358"><a name="p16225194616358"></a><a name="p16225194616358"></a><strong id="b1722524613356"><a name="b1722524613356"></a><a name="b1722524613356"></a>数据类型</strong></p>
</th>
<th class="cellrowborder" valign="top" width="43.03%" id="mcps1.2.5.1.4"><p id="p102251446143517"><a name="p102251446143517"></a><a name="p102251446143517"></a><strong id="b18225114653515"><a name="b18225114653515"></a><a name="b18225114653515"></a>取值范围</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row11788163121319"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p125529339138"><a name="p125529339138"></a><a name="p125529339138"></a>dim</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p17552633101319"><a name="p17552633101319"></a><a name="p17552633101319"></a>维度。</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p135521633171317"><a name="p135521633171317"></a><a name="p135521633171317"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p12552193321320"><a name="p12552193321320"></a><a name="p12552193321320"></a>[1,2000]</p>
</td>
</tr>
<tr id="row9706834203510"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p6902174915472"><a name="p6902174915472"></a><a name="p6902174915472"></a>pqM</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p17377175319523"><a name="p17377175319523"></a><a name="p17377175319523"></a>子空间数。</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p38481898457"><a name="p38481898457"></a><a name="p38481898457"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p15848209134510"><a name="p15848209134510"></a><a name="p15848209134510"></a>[1,dim]，其中<span class="parmname" id="parmname19863104816351"><a name="parmname19863104816351"></a><a name="parmname19863104816351"></a>“dim”</span>是结构体<span class="parmname" id="parmname9438142552910"><a name="parmname9438142552910"></a><a name="parmname9438142552910"></a>“PQParams”</span>中的字段，表示向量维度。</p>
</td>
</tr>
<tr id="row167067341356"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p169031449134713"><a name="p169031449134713"></a><a name="p169031449134713"></a>pqKsub</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p33781853165216"><a name="p33781853165216"></a><a name="p33781853165216"></a>子空间内聚类中心数。</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p2848159114511"><a name="p2848159114511"></a><a name="p2848159114511"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p28487964518"><a name="p28487964518"></a><a name="p28487964518"></a>[1,256]</p>
</td>
</tr>
<tr id="row3706173411353"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p15903249194711"><a name="p15903249194711"></a><a name="p15903249194711"></a>functype</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p10378553185217"><a name="p10378553185217"></a><a name="p10378553185217"></a>距离类型。</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p48488911458"><a name="p48488911458"></a><a name="p48488911458"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p1260341310305"><a name="p1260341310305"></a><a name="p1260341310305"></a>[1,3]</p>
<a name="ul7615133223018"></a><a name="ul7615133223018"></a><ul id="ul7615133223018"><li>1：表示L2类型。</li><li>2：表示IP类型。</li><li>3：表示Cosine类型。</li></ul>
</td>
</tr>
<tr id="row4707934123513"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p209032495474"><a name="p209032495474"></a><a name="p209032495474"></a>subItemSize</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p6378053195212"><a name="p6378053195212"></a><a name="p6378053195212"></a>码字大小。</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p2849991457"><a name="p2849991457"></a><a name="p2849991457"></a>size_t</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p98491298451"><a name="p98491298451"></a><a name="p98491298451"></a>限制非0。</p>
</td>
</tr>
<tr id="row1670718344353"><td class="cellrowborder" valign="top" width="16.27%" headers="mcps1.2.5.1.1 "><p id="p19903154912477"><a name="p19903154912477"></a><a name="p19903154912477"></a>pqTable</p>
</td>
<td class="cellrowborder" valign="top" width="21.82%" headers="mcps1.2.5.1.2 "><p id="p9378175375213"><a name="p9378175375213"></a><a name="p9378175375213"></a>码本。</p>
</td>
<td class="cellrowborder" valign="top" width="18.88%" headers="mcps1.2.5.1.3 "><p id="p88493920454"><a name="p88493920454"></a><a name="p88493920454"></a>char*</p>
</td>
<td class="cellrowborder" valign="top" width="43.03%" headers="mcps1.2.5.1.4 "><p id="p6849189154513"><a name="p6849189154513"></a><a name="p6849189154513"></a>限制非空。</p>
</td>
</tr>
</tbody>
</table>

## ComputePQTable

**接口定义<a name="section172317194488"></a>**

int ComputePQTable\(VectorArray samples, PQParams \*params\);

**接口用途<a name="section1153124784912"></a>**

计算PQ码本。

**参数说明<a name="section157501312135019"></a>**

<a name="table4285822103716"></a>
<table><thead align="left"><tr id="row1286152233717"><th class="cellrowborder" valign="top" width="15.39%" id="mcps1.1.5.1.1"><p id="p1028632213373"><a name="p1028632213373"></a><a name="p1028632213373"></a><strong id="b229432916375"><a name="b229432916375"></a><a name="b229432916375"></a>参数名称</strong></p>
</th>
<th class="cellrowborder" valign="top" width="19.24%" id="mcps1.1.5.1.2"><p id="p426420913521"><a name="p426420913521"></a><a name="p426420913521"></a><strong id="b1657933643718"><a name="b1657933643718"></a><a name="b1657933643718"></a>数据类型</strong></p>
</th>
<th class="cellrowborder" valign="top" width="35.3%" id="mcps1.1.5.1.3"><p id="p16579163614371"><a name="p16579163614371"></a><a name="p16579163614371"></a><strong id="b65791236113717"><a name="b65791236113717"></a><a name="b65791236113717"></a>描述</strong></p>
</th>
<th class="cellrowborder" valign="top" width="30.070000000000004%" id="mcps1.1.5.1.4"><p id="p1657912363375"><a name="p1657912363375"></a><a name="p1657912363375"></a><strong id="b55791367373"><a name="b55791367373"></a><a name="b55791367373"></a>取值范围</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row16286112213372"><td class="cellrowborder" valign="top" headers="mcps1.1.5.1.1 "><p id="p1244551123717"><a name="p1244551123717"></a><a name="p1244551123717"></a>samples</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.1.5.1.2 "><p id="p1726499165213"><a name="p1726499165213"></a><a name="p1726499165213"></a>VectorArray</p>
</td>
<td class="cellrowborder" colspan="2" valign="top" headers="mcps1.1.5.1.3 mcps1.1.5.1.4 "><p id="p928622293716"><a name="p928622293716"></a><a name="p928622293716"></a>字段描述请参见<a href="#结构体VectorArray字段描述">结构体说明</a>中的<span class="parmname" id="parmname0442121133711"><a name="parmname0442121133711"></a><a name="parmname0442121133711"></a>“VectorArray”</span>字段描述。</p>
</td>
</tr>
<tr id="row6286022173712"><td class="cellrowborder" valign="top" headers="mcps1.1.5.1.1 "><p id="p1596013543378"><a name="p1596013543378"></a><a name="p1596013543378"></a>params</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.1.5.1.2 "><p id="p226410910524"><a name="p226410910524"></a><a name="p226410910524"></a>PQParams</p>
</td>
<td class="cellrowborder" colspan="2" valign="top" headers="mcps1.1.5.1.3 mcps1.1.5.1.4 "><p id="p107381649203819"><a name="p107381649203819"></a><a name="p107381649203819"></a>字段描述请参见<a href="#结构体VectorArray字段描述">结构体说明</a>中的<span class="parmname" id="parmname7604423173715"><a name="parmname7604423173715"></a><a name="parmname7604423173715"></a>“PQParams”</span>字段描述。其中，<span class="parmname" id="parmname1493894154317"><a name="parmname1493894154317"></a><a name="parmname1493894154317"></a>“pqTable”</span>也可以作为输出值。</p>
</td>
</tr>
</tbody>
</table>

**返回值<a name="section49971832106"></a>**

<a name="table17997635100"></a>
<table><thead align="left"><tr id="row699763141018"><th class="cellrowborder" valign="top" width="40%" id="mcps1.1.3.1.1"><p id="p699793141012"><a name="p699793141012"></a><a name="p699793141012"></a>数据类型</p>
</th>
<th class="cellrowborder" valign="top" width="60%" id="mcps1.1.3.1.2"><p id="p1999763141020"><a name="p1999763141020"></a><a name="p1999763141020"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row1599716361015"><td class="cellrowborder" valign="top" width="40%" headers="mcps1.1.3.1.1 "><p id="p39970319101"><a name="p39970319101"></a><a name="p39970319101"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="60%" headers="mcps1.1.3.1.2 "><p id="p53461032104518"><a name="p53461032104518"></a><a name="p53461032104518"></a>正常运行时返回0，异常退出返回-1。</p>
</td>
</tr>
</tbody>
</table>

**使用示例**

```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kvecturbo.h"

int main() {
    // 参数配置
    int dim = 128;          // 向量维度
    int numSamples = 10000; // 训练样本数量
    int pqM = 8;            // 子空间数（dim需能被pqM整除）
    int pqKsub = 256;       // 每个子空间的聚类中心数
    int functype = 1;       // L2距离

    // 准备训练样本数据
    size_t dataSize = numSamples * dim * sizeof(float);
    float* sampleData = (float*)malloc(dataSize);
    if (sampleData == NULL) {
        printf("内存分配失败\n");
        return -1;
    }
    // ... 填充sampleData训练数据 ...
    for (int i = 0; i < numSamples * dim; i++) {
        sampleData[i] = (float)rand() / RAND_MAX;  // 示例：随机填充
    }

    // 初始化VectorArray结构体
    VectorArray samples;
    samples.maxLen = numSamples;
    samples.length = numSamples;
    samples.dim = dim;
    samples.itemSize = dim * sizeof(float);
    samples.items = (char*)sampleData;

    // 初始化PQParams结构体
    PQParams params;
    params.dim = dim;
    params.pqM = pqM;
    params.pqKsub = pqKsub;
    params.functype = functype;
    params.subItemSize = (dim / pqM) * sizeof(float);
    
    // 分配码本存储空间
    size_t pqTableSize = pqM * pqKsub * (dim / pqM) * sizeof(float);
    params.pqTable = (char*)malloc(pqTableSize);
    if (params.pqTable == NULL) {
        printf("码本内存分配失败\n");
        free(sampleData);
        return -1;
    }

    // 计算PQ码本
    int ret = ComputePQTable(samples, &params);

    if (ret != 0) {
        printf("计算PQ码本失败，错误码: %d\n", ret);
        free(sampleData);
        free(params.pqTable);
        return -1;
    }

    printf("成功计算PQ码本\n");
    printf("  - 子空间数: %d\n", pqM);
    printf("  - 每子空间聚类中心数: %d\n", pqKsub);

    // ... 使用params.pqTable进行后续量化操作 ...

    // 清理资源
    free(sampleData);
    free(params.pqTable);

    return 0;
}
```

## ComputeVectorPQCode

**接口定义<a name="section172317194488"></a>**

int ComputeVectorPQCode\(float \*vector, const PQParams \*params, unsigned char \*pqCode, size\_t pqCode\_size\);

**接口用途<a name="section1153124784912"></a>**

根据PQ码本，量化输入向量。

**参数说明<a name="section157501312135019"></a>**

<a name="table1646711617442"></a>
<table><thead align="left"><tr id="row846751612442"><th class="cellrowborder" valign="top" width="16.06%" id="mcps1.1.5.1.1"><p id="p1035755516441"><a name="p1035755516441"></a><a name="p1035755516441"></a><strong id="b535775554413"><a name="b535775554413"></a><a name="b535775554413"></a>参数名称</strong></p>
</th>
<th class="cellrowborder" valign="top" width="18.56%" id="mcps1.1.5.1.2"><p id="p335712558441"><a name="p335712558441"></a><a name="p335712558441"></a><strong id="b153571755154417"><a name="b153571755154417"></a><a name="b153571755154417"></a>数据类型</strong></p>
</th>
<th class="cellrowborder" valign="top" width="33.85%" id="mcps1.1.5.1.3"><p id="p577354119532"><a name="p577354119532"></a><a name="p577354119532"></a><strong id="b9773541165316"><a name="b9773541165316"></a><a name="b9773541165316"></a>描述</strong></p>
</th>
<th class="cellrowborder" valign="top" width="31.53%" id="mcps1.1.5.1.4"><p id="p8357955164412"><a name="p8357955164412"></a><a name="p8357955164412"></a><strong id="b335775510441"><a name="b335775510441"></a><a name="b335775510441"></a>取值范围</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row146815169448"><td class="cellrowborder" valign="top" width="16.06%" headers="mcps1.1.5.1.1 "><p id="p18290135419477"><a name="p18290135419477"></a><a name="p18290135419477"></a>vector</p>
</td>
<td class="cellrowborder" valign="top" width="18.56%" headers="mcps1.1.5.1.2 "><p id="p5290654174714"><a name="p5290654174714"></a><a name="p5290654174714"></a>float *</p>
</td>
<td class="cellrowborder" valign="top" width="33.85%" headers="mcps1.1.5.1.3 "><p id="p197735413538"><a name="p197735413538"></a><a name="p197735413538"></a>原始向量。</p>
</td>
<td class="cellrowborder" valign="top" width="31.53%" headers="mcps1.1.5.1.4 "><p id="p1829095424711"><a name="p1829095424711"></a><a name="p1829095424711"></a>限制非空。</p>
</td>
</tr>
<tr id="row18468216154410"><td class="cellrowborder" valign="top" width="16.06%" headers="mcps1.1.5.1.1 "><p id="p2290754114711"><a name="p2290754114711"></a><a name="p2290754114711"></a>pqCode</p>
</td>
<td class="cellrowborder" valign="top" width="18.56%" headers="mcps1.1.5.1.2 "><p id="p112901054164717"><a name="p112901054164717"></a><a name="p112901054164717"></a>unsigned char *</p>
</td>
<td class="cellrowborder" valign="top" width="33.85%" headers="mcps1.1.5.1.3 "><p id="p17773144119539"><a name="p17773144119539"></a><a name="p17773144119539"></a>量化后的向量。也可以作为输出值。</p>
</td>
<td class="cellrowborder" valign="top" width="31.53%" headers="mcps1.1.5.1.4 "><p id="p184321218164110"><a name="p184321218164110"></a><a name="p184321218164110"></a>限制非空。长度为pqCode_size，其中<span class="parmname" id="parmname5730023802"><a name="parmname5730023802"></a><a name="parmname5730023802"></a>“pqCode_size”</span>为量化后向量数组的长度。</p>
</td>
</tr>
<tr id="row1097711208581"><td class="cellrowborder" valign="top" width="16.06%" headers="mcps1.1.5.1.1 "><p id="p18978152020588"><a name="p18978152020588"></a><a name="p18978152020588"></a>pqCode_size</p>
</td>
<td class="cellrowborder" valign="top" width="18.56%" headers="mcps1.1.5.1.2 "><p id="p18978920195820"><a name="p18978920195820"></a><a name="p18978920195820"></a>size_t</p>
</td>
<td class="cellrowborder" valign="top" width="33.85%" headers="mcps1.1.5.1.3 "><p id="p1197892016583"><a name="p1197892016583"></a><a name="p1197892016583"></a>量化后向量数组的长度。</p>
</td>
<td class="cellrowborder" valign="top" width="31.53%" headers="mcps1.1.5.1.4 "><p id="p169783208589"><a name="p169783208589"></a><a name="p169783208589"></a>限制为pqM，其中<span class="parmname" id="parmname19863104816351"><a name="parmname19863104816351"></a><a name="parmname19863104816351"></a>“pqM”</span>是结构体<span class="parmname" id="parmname9438142552910"><a name="parmname9438142552910"></a><a name="parmname9438142552910"></a>“PQParams”</span>中的字段，表示子空间数。</p>
</td>
</tr>
<tr id="row746811684410"><td class="cellrowborder" valign="top" headers="mcps1.1.5.1.1 "><p id="p1329075411477"><a name="p1329075411477"></a><a name="p1329075411477"></a>params</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.1.5.1.2 "><p id="p8969751950"><a name="p8969751950"></a><a name="p8969751950"></a>const PQParams</p>
</td>
<td class="cellrowborder" colspan="2" valign="top" headers="mcps1.1.5.1.3 mcps1.1.5.1.4 "><p id="p107381649203819"><a name="p107381649203819"></a><a name="p107381649203819"></a>字段描述请参见<a href="#结构体VectorArray字段描述">结构体说明</a>中的<span class="parmname" id="parmname2632102712379"><a name="parmname2632102712379"></a><a name="parmname2632102712379"></a>“PQParams”</span>字段描述。</p>
</td>
</tr>
</tbody>
</table>

**返回值<a name="section49971832106"></a>**

<a name="table17997635100"></a>
<table><thead align="left"><tr id="row699763141018"><th class="cellrowborder" valign="top" width="40%" id="mcps1.1.3.1.1"><p id="p699793141012"><a name="p699793141012"></a><a name="p699793141012"></a>数据类型</p>
</th>
<th class="cellrowborder" valign="top" width="60%" id="mcps1.1.3.1.2"><p id="p1999763141020"><a name="p1999763141020"></a><a name="p1999763141020"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row1599716361015"><td class="cellrowborder" valign="top" width="40%" headers="mcps1.1.3.1.1 "><p id="p39970319101"><a name="p39970319101"></a><a name="p39970319101"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="60%" headers="mcps1.1.3.1.2 "><p id="p53461032104518"><a name="p53461032104518"></a><a name="p53461032104518"></a>正常运行时返回0，异常退出返回-1。</p>
</td>
</tr>
</tbody>
</table>

**使用示例**

```c++
#include <stdio.h>
#include <stdlib.h>
#include "kvecturbo.h"

int main() {
    // 假设已通过ComputePQTable计算得到PQ码本
    int dim = 128;
    int pqM = 8;
    int pqKsub = 256;
    
    // 初始化PQParams（假设pqTable已填充）
    PQParams params;
    params.dim = dim;
    params.pqM = pqM;
    params.pqKsub = pqKsub;
    params.functype = 1;  // L2距离
    params.subItemSize = (dim / pqM) * sizeof(float);
    
    // 分配并填充码本（实际应用中应使用ComputePQTable的输出）
    size_t pqTableSize = pqM * pqKsub * (dim / pqM) * sizeof(float);
    params.pqTable = (char*)malloc(pqTableSize);
    // ... 假设pqTable已通过ComputePQTable填充 ...

    // 准备待量化的原始向量
    float* vector = (float*)malloc(dim * sizeof(float));
    for (int i = 0; i < dim; i++) {
        vector[i] = (float)rand() / RAND_MAX;  // 示例数据
    }

    // 分配量化后的PQ码存储空间
    size_t pqCodeSize = pqM;  // 每个子空间一个码字（uint8）
    unsigned char* pqCode = (unsigned char*)malloc(pqCodeSize);

    // 执行向量量化
    int ret = ComputeVectorPQCode(vector, &params, pqCode, pqCodeSize);

    if (ret != 0) {
        printf("向量量化失败，错误码: %d\n", ret);
        free(vector);
        free(pqCode);
        free(params.pqTable);
        return -1;
    }

    printf("向量量化成功\n");
    printf("PQ码: ");
    for (size_t i = 0; i < pqCodeSize; i++) {
        printf("%u ", pqCode[i]);
    }
    printf("\n");

    // 清理资源
    free(vector);
    free(pqCode);
    free(params.pqTable);

    return 0;
}
```

## GetPQDistanceTableSdc

**接口定义<a name="section172317194488"></a>**

int GetPQDistanceTableSdc\(const PQParams \*params, float \*pqDistanceTable, size\_t pqDistanceTable\_size\);

**接口用途<a name="section1153124784912"></a>**

计算PQ SDC距离表，即计算各个子空间内聚类中心之间的距离。

**参数说明<a name="section157501312135019"></a>**

<a name="table1646711617442"></a>
<table><thead align="left"><tr id="row846751612442"><th class="cellrowborder" valign="top" width="18.94810518948105%" id="mcps1.1.5.1.1"><p id="p1035755516441"><a name="p1035755516441"></a><a name="p1035755516441"></a><strong id="b535775554413"><a name="b535775554413"></a><a name="b535775554413"></a>参数名称</strong></p>
</th>
<th class="cellrowborder" valign="top" width="17.408259174082595%" id="mcps1.1.5.1.2"><p id="p335712558441"><a name="p335712558441"></a><a name="p335712558441"></a><strong id="b153571755154417"><a name="b153571755154417"></a><a name="b153571755154417"></a>数据类型</strong></p>
</th>
<th class="cellrowborder" valign="top" width="31.586841315868412%" id="mcps1.1.5.1.3"><p id="p1161011635413"><a name="p1161011635413"></a><a name="p1161011635413"></a><strong id="b26101665540"><a name="b26101665540"></a><a name="b26101665540"></a>描述</strong></p>
</th>
<th class="cellrowborder" valign="top" width="32.056794320567946%" id="mcps1.1.5.1.4"><p id="p8357955164412"><a name="p8357955164412"></a><a name="p8357955164412"></a><strong id="b335775510441"><a name="b335775510441"></a><a name="b335775510441"></a>取值范围</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row146815169448"><td class="cellrowborder" valign="top" width="18.94810518948105%" headers="mcps1.1.5.1.1 "><p id="p19390163034918"><a name="p19390163034918"></a><a name="p19390163034918"></a>pqDistanceTable</p>
</td>
<td class="cellrowborder" valign="top" width="17.408259174082595%" headers="mcps1.1.5.1.2 "><p id="p11390103044916"><a name="p11390103044916"></a><a name="p11390103044916"></a>float*</p>
</td>
<td class="cellrowborder" valign="top" width="31.586841315868412%" headers="mcps1.1.5.1.3 "><p id="p1461013614543"><a name="p1461013614543"></a><a name="p1461013614543"></a>SDC距离表。也可以作为输出值。</p>
</td>
<td class="cellrowborder" valign="top" width="32.056794320567946%" headers="mcps1.1.5.1.4 "><p id="p93901930134918"><a name="p93901930134918"></a><a name="p93901930134918"></a>限制非空。长度为pqDistanceTable_size，其中<span class="parmname" id="parmname5730023802"><a name="parmname5730023802"></a><a name="parmname5730023802"></a>“pqDistanceTable_size”</span>为SDC距离表数组的长度。</p>
</td>
</tr>
<tr id="row1827017313116"><td class="cellrowborder" valign="top" width="18.94810518948105%" headers="mcps1.1.5.1.1 "><p id="p17270143818"><a name="p17270143818"></a><a name="p17270143818"></a>pqDistanceTable_size</p>
</td>
<td class="cellrowborder" valign="top" width="17.408259174082595%" headers="mcps1.1.5.1.2 "><p id="p32701332011"><a name="p32701332011"></a><a name="p32701332011"></a>size_t</p>
</td>
<td class="cellrowborder" valign="top" width="31.586841315868412%" headers="mcps1.1.5.1.3 "><p id="p18270031811"><a name="p18270031811"></a><a name="p18270031811"></a>SDC距离表数组的长度。</p>
</td>
<td class="cellrowborder" valign="top" width="32.056794320567946%" headers="mcps1.1.5.1.4 "><p id="p2270133219"><a name="p2270133219"></a><a name="p2270133219"></a>限制为pqM*pqKsub*pqKsub，其中<span class="parmname" id="parmname19863104816351"><a name="parmname19863104816351"></a><a name="parmname19863104816351"></a>“pqM”</span>是结构体<span class="parmname" id="parmname9438142552910"><a name="parmname9438142552910"></a><a name="parmname9438142552910"></a>“PQParams”</span>中的字段，表示子空间数，<span class="parmname" id="parmname1924714131720"><a name="parmname1924714131720"></a><a name="parmname1924714131720"></a>“pqKsub”</span>是结构体<span class="parmname" id="parmname17247413229"><a name="parmname17247413229"></a><a name="parmname17247413229"></a>“PQParams”</span>中的字段，表示子空间内聚类中心数。</p>
</td>
</tr>
<tr id="row18468216154410"><td class="cellrowborder" valign="top" headers="mcps1.1.5.1.1 "><p id="p129318508517"><a name="p129318508517"></a><a name="p129318508517"></a>params</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.1.5.1.2 "><p id="p550413473510"><a name="p550413473510"></a><a name="p550413473510"></a>const PQParams</p>
</td>
<td class="cellrowborder" colspan="2" valign="top" headers="mcps1.1.5.1.3 mcps1.1.5.1.4 "><p id="p107381649203819"><a name="p107381649203819"></a><a name="p107381649203819"></a>字段描述请参见<a href="#结构体VectorArray字段描述">结构体说明</a>中的<span class="parmname" id="parmname1734613325371"><a name="parmname1734613325371"></a><a name="parmname1734613325371"></a>“PQParams”</span>字段描述。</p>
</td>
</tr>
</tbody>
</table>

**返回值<a name="section49971832106"></a>**

<a name="table17997635100"></a>
<table><thead align="left"><tr id="row699763141018"><th class="cellrowborder" valign="top" width="40%" id="mcps1.1.3.1.1"><p id="p699793141012"><a name="p699793141012"></a><a name="p699793141012"></a>数据类型</p>
</th>
<th class="cellrowborder" valign="top" width="60%" id="mcps1.1.3.1.2"><p id="p1999763141020"><a name="p1999763141020"></a><a name="p1999763141020"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row1599716361015"><td class="cellrowborder" valign="top" width="40%" headers="mcps1.1.3.1.1 "><p id="p39970319101"><a name="p39970319101"></a><a name="p39970319101"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="60%" headers="mcps1.1.3.1.2 "><p id="p53461032104518"><a name="p53461032104518"></a><a name="p53461032104518"></a>正常运行时返回0，异常退出返回-1。</p>
</td>
</tr>
</tbody>
</table>

**使用示例**

```c++
#include <stdio.h>
#include <stdlib.h>
#include "kvecturbo.h"

int main() {
    // 假设已通过ComputePQTable计算得到PQ码本
    int dim = 128;
    int pqM = 8;
    int pqKsub = 256;
    
    // 初始化PQParams（假设pqTable已填充）
    PQParams params;
    params.dim = dim;
    params.pqM = pqM;
    params.pqKsub = pqKsub;
    params.functype = 1;  // L2距离
    params.subItemSize = (dim / pqM) * sizeof(float);
    
    size_t pqTableSize = pqM * pqKsub * (dim / pqM) * sizeof(float);
    params.pqTable = (char*)malloc(pqTableSize);
    // ... 假设pqTable已通过ComputePQTable填充 ...

    // 计算SDC距离表大小并分配内存
    // SDC表存储每个子空间内所有聚类中心对之间的距离
    size_t sdcTableSize = pqM * pqKsub * pqKsub;
    float* sdcDistanceTable = (float*)malloc(sdcTableSize * sizeof(float));
    if (sdcDistanceTable == NULL) {
        printf("SDC距离表内存分配失败\n");
        free(params.pqTable);
        return -1;
    }

    // 计算SDC距离表
    int ret = GetPQDistanceTableSdc(&params, sdcDistanceTable, sdcTableSize);

    if (ret != 0) {
        printf("计算SDC距离表失败，错误码: %d\n", ret);
        free(sdcDistanceTable);
        free(params.pqTable);
        return -1;
    }

    printf("成功计算SDC距离表\n");
    printf("  - 距离表大小: %zu\n", sdcTableSize);
    printf("  - 第一个子空间中心0与中心1的距离: %f\n", sdcDistanceTable[1]);

    // ... 使用SDC距离表进行后续距离计算 ...

    // 清理资源
    free(sdcDistanceTable);
    free(params.pqTable);

    return 0;
}
```

## GetPQDistanceTableAdc

**接口定义<a name="section172317194488"></a>**

int GetPQDistanceTableAdc\(float\* vector, const PQParams \*params, float \*pqDistanceTable, size\_t pqDistanceTable\_size\);

**接口用途<a name="section1153124784912"></a>**

计算PQ ADC距离表，即计算查询向量和各个子空间内聚类中心的距离。

**参数说明<a name="section157501312135019"></a>**

<a name="table1646711617442"></a>
<table><thead align="left"><tr id="row846751612442"><th class="cellrowborder" valign="top" width="18.34%" id="mcps1.1.5.1.1"><p id="p1035755516441"><a name="p1035755516441"></a><a name="p1035755516441"></a><strong id="b535775554413"><a name="b535775554413"></a><a name="b535775554413"></a>参数名称</strong></p>
</th>
<th class="cellrowborder" valign="top" width="16.11%" id="mcps1.1.5.1.2"><p id="p335712558441"><a name="p335712558441"></a><a name="p335712558441"></a><strong id="b153571755154417"><a name="b153571755154417"></a><a name="b153571755154417"></a>数据类型</strong></p>
</th>
<th class="cellrowborder" valign="top" width="35.23%" id="mcps1.1.5.1.3"><p id="p11531628175416"><a name="p11531628175416"></a><a name="p11531628175416"></a><strong id="b15372812545"><a name="b15372812545"></a><a name="b15372812545"></a>描述</strong></p>
</th>
<th class="cellrowborder" valign="top" width="30.320000000000004%" id="mcps1.1.5.1.4"><p id="p8357955164412"><a name="p8357955164412"></a><a name="p8357955164412"></a><strong id="b335775510441"><a name="b335775510441"></a><a name="b335775510441"></a>取值范围</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row146815169448"><td class="cellrowborder" valign="top" width="18.34%" headers="mcps1.1.5.1.1 "><p id="p3391114550"><a name="p3391114550"></a><a name="p3391114550"></a>vector</p>
</td>
<td class="cellrowborder" valign="top" width="16.11%" headers="mcps1.1.5.1.2 "><p id="p1539161116559"><a name="p1539161116559"></a><a name="p1539161116559"></a>float*</p>
</td>
<td class="cellrowborder" valign="top" width="35.23%" headers="mcps1.1.5.1.3 "><p id="p19533285546"><a name="p19533285546"></a><a name="p19533285546"></a>原始向量。</p>
</td>
<td class="cellrowborder" valign="top" width="30.320000000000004%" headers="mcps1.1.5.1.4 "><p id="p153918116557"><a name="p153918116557"></a><a name="p153918116557"></a>限制非空。</p>
</td>
</tr>
<tr id="row18468216154410"><td class="cellrowborder" valign="top" width="18.34%" headers="mcps1.1.5.1.1 "><p id="p939711155514"><a name="p939711155514"></a><a name="p939711155514"></a>pqDistanceTable</p>
</td>
<td class="cellrowborder" valign="top" width="16.11%" headers="mcps1.1.5.1.2 "><p id="p439181115515"><a name="p439181115515"></a><a name="p439181115515"></a>float*</p>
</td>
<td class="cellrowborder" valign="top" width="35.23%" headers="mcps1.1.5.1.3 "><p id="p45318284546"><a name="p45318284546"></a><a name="p45318284546"></a>ADC距离表。也可以作为输出值。</p>
</td>
<td class="cellrowborder" valign="top" width="30.320000000000004%" headers="mcps1.1.5.1.4 "><p id="p143911120557"><a name="p143911120557"></a><a name="p143911120557"></a>限制非空。长度为pqDistanceTable_size，其中<span class="parmname" id="parmname5730023802"><a name="parmname5730023802"></a><a name="parmname5730023802"></a>“pqDistanceTable_size”</span>为ADC距离表数组的长度。</p>
</td>
</tr>
<tr id="row44811238446"><td class="cellrowborder" valign="top" width="18.34%" headers="mcps1.1.5.1.1 "><p id="p17270143818"><a name="p17270143818"></a><a name="p17270143818"></a>pqDistanceTable_size</p>
</td>
<td class="cellrowborder" valign="top" width="16.11%" headers="mcps1.1.5.1.2 "><p id="p32701332011"><a name="p32701332011"></a><a name="p32701332011"></a>size_t</p>
</td>
<td class="cellrowborder" valign="top" width="35.23%" headers="mcps1.1.5.1.3 "><p id="p18270031811"><a name="p18270031811"></a><a name="p18270031811"></a>ADC距离表数组的长度。</p>
</td>
<td class="cellrowborder" valign="top" width="30.320000000000004%" headers="mcps1.1.5.1.4 "><p id="p2270133219"><a name="p2270133219"></a><a name="p2270133219"></a>限制为pqM*pqKsub*pqKsub，其中<span class="parmname" id="parmname19863104816351"><a name="parmname19863104816351"></a><a name="parmname19863104816351"></a>“pqM”</span>是结构体<span class="parmname" id="parmname9438142552910"><a name="parmname9438142552910"></a><a name="parmname9438142552910"></a>“PQParams”</span>中的字段，表示子空间数，<span class="parmname" id="parmname1924714131720"><a name="parmname1924714131720"></a><a name="parmname1924714131720"></a>“pqKsub”</span>是结构体<span class="parmname" id="parmname17247413229"><a name="parmname17247413229"></a><a name="parmname17247413229"></a>“PQParams”</span>中的字段，表示子空间内聚类中心数。</p>
</td>
</tr>
<tr id="row746811684410"><td class="cellrowborder" valign="top" headers="mcps1.1.5.1.1 "><p id="p26190151167"><a name="p26190151167"></a><a name="p26190151167"></a>params</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.1.5.1.2 "><p id="p674585615524"><a name="p674585615524"></a><a name="p674585615524"></a>const PQParams</p>
</td>
<td class="cellrowborder" colspan="2" valign="top" headers="mcps1.1.5.1.3 mcps1.1.5.1.4 "><p id="p184692620448"><a name="p184692620448"></a><a name="p184692620448"></a>字段描述请参见<a href="#结构体VectorArray字段描述">结构体说明</a>中的<span class="parmname" id="parmname1163683593716"><a name="parmname1163683593716"></a><a name="parmname1163683593716"></a>“PQParams”</span>字段描述。</p>
</td>
</tr>
</tbody>
</table>

**返回值<a name="section49971832106"></a>**

<a name="table17997635100"></a>
<table><thead align="left"><tr id="row699763141018"><th class="cellrowborder" valign="top" width="40%" id="mcps1.1.3.1.1"><p id="p699793141012"><a name="p699793141012"></a><a name="p699793141012"></a>数据类型</p>
</th>
<th class="cellrowborder" valign="top" width="60%" id="mcps1.1.3.1.2"><p id="p1999763141020"><a name="p1999763141020"></a><a name="p1999763141020"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row1599716361015"><td class="cellrowborder" valign="top" width="40%" headers="mcps1.1.3.1.1 "><p id="p39970319101"><a name="p39970319101"></a><a name="p39970319101"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="60%" headers="mcps1.1.3.1.2 "><p id="p53461032104518"><a name="p53461032104518"></a><a name="p53461032104518"></a>正常运行时返回0，异常退出返回-1。</p>
</td>
</tr>
</tbody>
</table>

**使用示例**

```c++
#include <stdio.h>
#include <stdlib.h>
#include "kvecturbo.h"

int main() {
    // 假设已通过ComputePQTable计算得到PQ码本
    int dim = 128;
    int pqM = 8;
    int pqKsub = 256;
    
    // 初始化PQParams（假设pqTable已填充）
    PQParams params;
    params.dim = dim;
    params.pqM = pqM;
    params.pqKsub = pqKsub;
    params.functype = 1;  // L2距离
    params.subItemSize = (dim / pqM) * sizeof(float);
    
    size_t pqTableSize = pqM * pqKsub * (dim / pqM) * sizeof(float);
    params.pqTable = (char*)malloc(pqTableSize);
    // ... 假设pqTable已通过ComputePQTable填充 ...

    // 准备查询向量
    float* queryVector = (float*)malloc(dim * sizeof(float));
    for (int i = 0; i < dim; i++) {
        queryVector[i] = (float)rand() / RAND_MAX;  // 示例数据
    }

    // 计算ADC距离表大小并分配内存
    // ADC表存储查询向量与每个子空间内所有聚类中心的距离
    size_t adcTableSize = pqM * pqKsub;
    float* adcDistanceTable = (float*)malloc(adcTableSize * sizeof(float));
    if (adcDistanceTable == NULL) {
        printf("ADC距离表内存分配失败\n");
        free(queryVector);
        free(params.pqTable);
        return -1;
    }

    // 计算ADC距离表
    int ret = GetPQDistanceTableAdc(queryVector, &params, adcDistanceTable, adcTableSize);

    if (ret != 0) {
        printf("计算ADC距离表失败，错误码: %d\n", ret);
        free(adcDistanceTable);
        free(queryVector);
        free(params.pqTable);
        return -1;
    }

    printf("成功计算ADC距离表\n");
    printf("  - 距离表大小: %zu\n", adcTableSize);
    printf("  - 查询向量与子空间0中心0的距离: %f\n", adcDistanceTable[0]);

    // ... 使用ADC距离表进行后续距离计算 ...

    // 清理资源
    free(adcDistanceTable);
    free(queryVector);
    free(params.pqTable);

    return 0;
}
```

## GetPQDistance

**接口定义<a name="section172317194488"></a>**

int GetPQDistance\(const unsigned char \*basecode, const unsigned char \*querycode, const PQParams \*params, const float \*pqDistanceTable, float \*PQDistance, size\_t basecode\_size, size\_t querycode\_size, size\_t pqDistanceTable\_size, size\_t pqDistance\_size\);

**接口用途<a name="section1153124784912"></a>**

计算PQ ADC或SDC距离。若querycode == NULL，计算的是ADC距离；若querycode != NULL，计算的是SDC距离。

**参数说明<a name="section157501312135019"></a>**

<a name="table1646711617442"></a>
<table><thead align="left"><tr id="row846751612442"><th class="cellrowborder" valign="top" width="17.588241175882413%" id="mcps1.1.5.1.1"><p id="p1035755516441"><a name="p1035755516441"></a><a name="p1035755516441"></a><strong id="b535775554413"><a name="b535775554413"></a><a name="b535775554413"></a>参数名称</strong></p>
</th>
<th class="cellrowborder" valign="top" width="21.18788121187881%" id="mcps1.1.5.1.2"><p id="p335712558441"><a name="p335712558441"></a><a name="p335712558441"></a><strong id="b153571755154417"><a name="b153571755154417"></a><a name="b153571755154417"></a>数据类型</strong></p>
</th>
<th class="cellrowborder" valign="top" width="35.24647535246475%" id="mcps1.1.5.1.3"><p id="p11785165413"><a name="p11785165413"></a><a name="p11785165413"></a><strong id="b177251165410"><a name="b177251165410"></a><a name="b177251165410"></a>描述</strong></p>
</th>
<th class="cellrowborder" valign="top" width="25.977402259774017%" id="mcps1.1.5.1.4"><p id="p8357955164412"><a name="p8357955164412"></a><a name="p8357955164412"></a><strong id="b335775510441"><a name="b335775510441"></a><a name="b335775510441"></a>取值范围</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row146815169448"><td class="cellrowborder" valign="top" width="17.588241175882413%" headers="mcps1.1.5.1.1 "><p id="p1563124410561"><a name="p1563124410561"></a><a name="p1563124410561"></a>basecode</p>
</td>
<td class="cellrowborder" valign="top" width="21.18788121187881%" headers="mcps1.1.5.1.2 "><p id="p956394495618"><a name="p956394495618"></a><a name="p956394495618"></a>unsigned char*</p>
</td>
<td class="cellrowborder" valign="top" width="35.24647535246475%" headers="mcps1.1.5.1.3 "><p id="p9755115414"><a name="p9755115414"></a><a name="p9755115414"></a>量化后的base。</p>
</td>
<td class="cellrowborder" valign="top" width="25.977402259774017%" headers="mcps1.1.5.1.4 "><p id="p156334415617"><a name="p156334415617"></a><a name="p156334415617"></a>限制非空。</p>
</td>
</tr>
<tr id="row18468216154410"><td class="cellrowborder" valign="top" width="17.588241175882413%" headers="mcps1.1.5.1.1 "><p id="p125631744155611"><a name="p125631744155611"></a><a name="p125631744155611"></a>querycode</p>
</td>
<td class="cellrowborder" valign="top" width="21.18788121187881%" headers="mcps1.1.5.1.2 "><p id="p1956313447562"><a name="p1956313447562"></a><a name="p1956313447562"></a>unsigned char*</p>
</td>
<td class="cellrowborder" valign="top" width="35.24647535246475%" headers="mcps1.1.5.1.3 "><p id="p379518542"><a name="p379518542"></a><a name="p379518542"></a>量化后的query。</p>
</td>
<td class="cellrowborder" valign="top" width="25.977402259774017%" headers="mcps1.1.5.1.4 "><p id="p215516591885"><a name="p215516591885"></a><a name="p215516591885"></a>-</p>
</td>
</tr>
<tr id="row746811684410"><td class="cellrowborder" valign="top" width="17.588241175882413%" headers="mcps1.1.5.1.1 "><p id="p1056334411567"><a name="p1056334411567"></a><a name="p1056334411567"></a>pqDistanceTable</p>
</td>
<td class="cellrowborder" valign="top" width="21.18788121187881%" headers="mcps1.1.5.1.2 "><p id="p11563544205617"><a name="p11563544205617"></a><a name="p11563544205617"></a>float*</p>
</td>
<td class="cellrowborder" valign="top" width="35.24647535246475%" headers="mcps1.1.5.1.3 "><p id="p15835185413"><a name="p15835185413"></a><a name="p15835185413"></a>SDC/ADC距离表。</p>
</td>
<td class="cellrowborder" valign="top" width="25.977402259774017%" headers="mcps1.1.5.1.4 "><p id="p6563174415562"><a name="p6563174415562"></a><a name="p6563174415562"></a>限制非空。</p>
</td>
</tr>
<tr id="row84681167446"><td class="cellrowborder" valign="top" width="17.588241175882413%" headers="mcps1.1.5.1.1 "><p id="p2563444175617"><a name="p2563444175617"></a><a name="p2563444175617"></a>PQDistance</p>
</td>
<td class="cellrowborder" valign="top" width="21.18788121187881%" headers="mcps1.1.5.1.2 "><p id="p8563164416569"><a name="p8563164416569"></a><a name="p8563164416569"></a>float*</p>
</td>
<td class="cellrowborder" valign="top" width="35.24647535246475%" headers="mcps1.1.5.1.3 "><p id="p118155155413"><a name="p118155155413"></a><a name="p118155155413"></a>SDC/ADC距离。</p>
</td>
<td class="cellrowborder" valign="top" width="25.977402259774017%" headers="mcps1.1.5.1.4 "><p id="p17563744115619"><a name="p17563744115619"></a><a name="p17563744115619"></a>限制非空。</p>
</td>
</tr>
<tr id="row7632211969"><td class="cellrowborder" valign="top" width="17.588241175882413%" headers="mcps1.1.5.1.1 "><p id="p147365121966"><a name="p147365121966"></a><a name="p147365121966"></a>basecode_size</p>
</td>
<td class="cellrowborder" valign="top" width="21.18788121187881%" headers="mcps1.1.5.1.2 "><p id="p196328113620"><a name="p196328113620"></a><a name="p196328113620"></a>size_t</p>
</td>
<td class="cellrowborder" valign="top" width="35.24647535246475%" headers="mcps1.1.5.1.3 "><p id="p6632711166"><a name="p6632711166"></a><a name="p6632711166"></a>量化后的base数组的长度。</p>
</td>
<td class="cellrowborder" valign="top" width="25.977402259774017%" headers="mcps1.1.5.1.4 "><p id="p46321611562"><a name="p46321611562"></a><a name="p46321611562"></a>限制为pqM，其中<span class="parmname" id="parmname19863104816351"><a name="parmname19863104816351"></a><a name="parmname19863104816351"></a>“pqM”</span>是结构体<span class="parmname" id="parmname9438142552910"><a name="parmname9438142552910"></a><a name="parmname9438142552910"></a>“PQParams”</span>中的字段，表示子空间数。</p>
</td>
</tr>
<tr id="row7553121017617"><td class="cellrowborder" valign="top" width="17.588241175882413%" headers="mcps1.1.5.1.1 "><p id="p1173613121166"><a name="p1173613121166"></a><a name="p1173613121166"></a>querycode_size</p>
</td>
<td class="cellrowborder" valign="top" width="21.18788121187881%" headers="mcps1.1.5.1.2 "><p id="p155310101968"><a name="p155310101968"></a><a name="p155310101968"></a>size_t</p>
</td>
<td class="cellrowborder" valign="top" width="35.24647535246475%" headers="mcps1.1.5.1.3 "><p id="p135531100620"><a name="p135531100620"></a><a name="p135531100620"></a>量化后的query数组的长度。</p>
</td>
<td class="cellrowborder" valign="top" width="25.977402259774017%" headers="mcps1.1.5.1.4 "><p id="p11553151016614"><a name="p11553151016614"></a><a name="p11553151016614"></a>若querycode非空，限制为pqM，其中<span class="parmname" id="parmname164661619109"><a name="parmname164661619109"></a><a name="parmname164661619109"></a>“querycode”</span>表示量化后的query，<span class="parmname" id="parmname776313131872"><a name="parmname776313131872"></a><a name="parmname776313131872"></a>“pqM”</span>是结构体<span class="parmname" id="parmname147634134712"><a name="parmname147634134712"></a><a name="parmname147634134712"></a>“PQParams”</span>中的字段，表示子空间数。</p>
</td>
</tr>
<tr id="row13989131111620"><td class="cellrowborder" valign="top" width="17.588241175882413%" headers="mcps1.1.5.1.1 "><p id="p137361312160"><a name="p137361312160"></a><a name="p137361312160"></a>pqDistanceTable_size</p>
</td>
<td class="cellrowborder" valign="top" width="21.18788121187881%" headers="mcps1.1.5.1.2 "><p id="p159891111464"><a name="p159891111464"></a><a name="p159891111464"></a>size_t</p>
</td>
<td class="cellrowborder" valign="top" width="35.24647535246475%" headers="mcps1.1.5.1.3 "><p id="p39890111161"><a name="p39890111161"></a><a name="p39890111161"></a>SDC/ADC距离表数组的长度。</p>
</td>
<td class="cellrowborder" valign="top" width="25.977402259774017%" headers="mcps1.1.5.1.4 "><p id="p189890111611"><a name="p189890111611"></a><a name="p189890111611"></a>若querycode为空时，限制为pqM*pqKsub，querycode非空时，限制为pqM*pqKsub*pqKsub，其中<span class="parmname" id="parmname8580192761111"><a name="parmname8580192761111"></a><a name="parmname8580192761111"></a>“querycode”</span>表示量化后的query，<span class="parmname" id="parmname25251614476"><a name="parmname25251614476"></a><a name="parmname25251614476"></a>“pqM”</span>是结构体<span class="parmname" id="parmname17525111417715"><a name="parmname17525111417715"></a><a name="parmname17525111417715"></a>“PQParams”</span>中的字段，表示子空间数，<span class="parmname" id="parmname1652519141777"><a name="parmname1652519141777"></a><a name="parmname1652519141777"></a>“pqKsub”</span>是结构体<span class="parmname" id="parmname1752519141579"><a name="parmname1752519141579"></a><a name="parmname1752519141579"></a>“PQParams”</span>中的字段，表示子空间内聚类中心数。</p>
</td>
</tr>
<tr id="row8727198062"><td class="cellrowborder" valign="top" width="17.588241175882413%" headers="mcps1.1.5.1.1 "><p id="p19736201215610"><a name="p19736201215610"></a><a name="p19736201215610"></a>PQDistance_size</p>
</td>
<td class="cellrowborder" valign="top" width="21.18788121187881%" headers="mcps1.1.5.1.2 "><p id="p20727681562"><a name="p20727681562"></a><a name="p20727681562"></a>size_t</p>
</td>
<td class="cellrowborder" valign="top" width="35.24647535246475%" headers="mcps1.1.5.1.3 "><p id="p67271482618"><a name="p67271482618"></a><a name="p67271482618"></a>SDC/ADC距离数组的长度。</p>
</td>
<td class="cellrowborder" valign="top" width="25.977402259774017%" headers="mcps1.1.5.1.4 "><p id="p197271781460"><a name="p197271781460"></a><a name="p197271781460"></a>限制为1。</p>
</td>
</tr>
<tr id="row13649153083811"><td class="cellrowborder" valign="top" headers="mcps1.1.5.1.1 "><p id="p18649930173810"><a name="p18649930173810"></a><a name="p18649930173810"></a>params</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.1.5.1.2 "><p id="p1358611261262"><a name="p1358611261262"></a><a name="p1358611261262"></a>const PQParams</p>
</td>
<td class="cellrowborder" colspan="2" valign="top" headers="mcps1.1.5.1.3 mcps1.1.5.1.4 "><p id="p107381649203819"><a name="p107381649203819"></a><a name="p107381649203819"></a>字段描述请参见<a href="#结构体VectorArray字段描述">结构体说明</a>中的<span class="parmname" id="parmname1724484014373"><a name="parmname1724484014373"></a><a name="parmname1724484014373"></a>“PQParams”</span>字段描述。</p>
</td>
</tr>
</tbody>
</table>

**返回值<a name="section49971832106"></a>**

<a name="table17997635100"></a>
<table><thead align="left"><tr id="row699763141018"><th class="cellrowborder" valign="top" width="40%" id="mcps1.1.3.1.1"><p id="p699793141012"><a name="p699793141012"></a><a name="p699793141012"></a>数据类型</p>
</th>
<th class="cellrowborder" valign="top" width="60%" id="mcps1.1.3.1.2"><p id="p1999763141020"><a name="p1999763141020"></a><a name="p1999763141020"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row1599716361015"><td class="cellrowborder" valign="top" width="40%" headers="mcps1.1.3.1.1 "><p id="p39970319101"><a name="p39970319101"></a><a name="p39970319101"></a>int</p>
</td>
<td class="cellrowborder" valign="top" width="60%" headers="mcps1.1.3.1.2 "><p id="p53461032104518"><a name="p53461032104518"></a><a name="p53461032104518"></a>正常运行时返回0，异常退出返回-1。</p>
</td>
</tr>
</tbody>
</table>

**使用示例**

```c++
#include <stdio.h>
#include <stdlib.h>
#include "kvecturbo.h"

int main() {
    int dim = 128;
    int pqM = 8;
    int pqKsub = 256;
    
    // 初始化PQParams（假设pqTable已填充）
    PQParams params;
    params.dim = dim;
    params.pqM = pqM;
    params.pqKsub = pqKsub;
    params.functype = 1;  // L2距离
    params.subItemSize = (dim / pqM) * sizeof(float);
    
    size_t pqTableSize = pqM * pqKsub * (dim / pqM) * sizeof(float);
    params.pqTable = (char*)malloc(pqTableSize);
    // ... 假设pqTable已通过ComputePQTable填充 ...

    // 准备base和query向量的PQ码（假设已通过ComputeVectorPQCode得到）
    unsigned char* basecode = (unsigned char*)malloc(pqM);
    unsigned char* querycode = (unsigned char*)malloc(pqM);
    for (int i = 0; i < pqM; i++) {
        basecode[i] = rand() % pqKsub;
        querycode[i] = rand() % pqKsub;
    }

    // 准备查询向量（用于ADC距离计算）
    float* queryVector = (float*)malloc(dim * sizeof(float));
    for (int i = 0; i < dim; i++) {
        queryVector[i] = (float)rand() / RAND_MAX;
    }

    float pqDistance = 0.0f;
    int ret;

    // ========== 方式1：计算ADC距离（querycode为NULL） ==========
    // ADC距离表大小：pqM * pqKsub
    size_t adcTableSize = pqM * pqKsub;
    float* adcDistanceTable = (float*)malloc(adcTableSize * sizeof(float));
    GetPQDistanceTableAdc(queryVector, &params, adcDistanceTable, adcTableSize);

    ret = GetPQDistance(
        basecode,           // 量化后的base
        NULL,               // querycode为NULL，计算ADC距离
        &params,
        adcDistanceTable,
        &pqDistance,
        pqM,                // basecode_size
        0,                  // querycode_size（querycode为NULL时无意义）
        adcTableSize,       // ADC距离表大小
        1                   // 输出距离数组大小
    );

    if (ret == 0) {
        printf("ADC距离: %f\n", pqDistance);
    }

    // ========== 方式2：计算SDC距离（querycode非NULL） ==========
    // SDC距离表大小：pqM * pqKsub * pqKsub
    size_t sdcTableSize = pqM * pqKsub * pqKsub;
    float* sdcDistanceTable = (float*)malloc(sdcTableSize * sizeof(float));
    GetPQDistanceTableSdc(&params, sdcDistanceTable, sdcTableSize);

    ret = GetPQDistance(
        basecode,           // 量化后的base
        querycode,          // querycode非NULL，计算SDC距离
        &params,
        sdcDistanceTable,
        &pqDistance,
        pqM,                // basecode_size
        pqM,                // querycode_size
        sdcTableSize,       // SDC距离表大小
        1                   // 输出距离数组大小
    );

    if (ret == 0) {
        printf("SDC距离: %f\n", pqDistance);
    }

    // 清理资源
    free(queryVector);
    free(adcDistanceTable);
    free(sdcDistanceTable);
    free(basecode);
    free(querycode);
    free(params.pqTable);

    return 0;
}
```
