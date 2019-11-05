#ifndef DCDC_header_H
#define DCDC_header_H

#ifdef __cplusplus
extern "C" {
#endif

//!defines
//--------------------------瀹忓畾涔�----------------------------------------------
				
//-----------------------鍙傛暟鐩稿叧瀹忓畾涔�-----------------------------------------
//--------------------------鐗堟湰淇℃伅-----------------------------------------------
#define MC_TYPE 			2010			//鏈哄瀷鍙傛暟
#define MC_REV 				210				//杞欢鐗堟湰鍙凤紙dot2锛�
#define MC_DATE 			2010			//鍑哄巶鏃ユ湡
#define MC_ID				1				//浜у搧缂栧彿
#define MC_WRKEY			999				//鍔熻兘鐮佷慨鏀瑰瘑鐮�
#define MC_MYKEY			1021			//鍒堕�鍟嗕娇鐢ㄧ殑瀵嗙爜

//------------------------鐢垫満杞瓙鍙嶅簭鎺у埗閫夋嫨-201005atcpc-----------------------------------------
#define	R_PHORDE			1				          //寮�

//********************************************************************************************//
//===================棰濆畾鐢垫祦鍩哄噯鍊煎嘲鍊硷紙姣忔瀹為獙鏍规嵁闇�鏇存敼锛�====================================
//#define NPR_IACN  473        //缃戜晶棰濆畾鐢垫祦鍩哄噯鍊�棰濆畾鏈夋晥鍊间负334A
//#define MPR_IACN  545        //鏈轰晶棰濆畾鐢垫祦鍩哄噯鍊�棰濆畾鏈夋晥鍊间负385A
#define NPR_IACN  682        //缃戜晶棰濆畾鐢垫祦鍩哄噯鍊�201205LVRTatZB LVRT瀹為獙鏀瑰ぇ 20120601night
#define MPR_IACN  682        //鏈轰晶棰濆畾鐢垫祦鍩哄噯鍊�棰濆畾鏈夋晥鍊间负482A 201107HC
#define STA_IACN  1000       //瀹氬瓙棰濆畾鐢垫祦鍩哄噯鍊�
#define GRD_UN    563        //棰濆畾鐢电綉鐩哥數鍘嬪嘲鍊�90V绯荤粺
#define CHOP_IDCN 650        //dc-chopper鐢垫祦淇濇姢棰濆畾鍊糂JTULVRT201204

//********************************************************************************************//
 
//----------------------------绯荤粺宸ヤ綔甯告暟------------------------------------------------

#define NPR_L       0.5e-3     //缃戜晶婊ゆ尝鐢垫劅鍊硷紙H锛�
#define MPR_L	    0.071e-3   //鏈轰晶dv/dt鐢垫劅鍊�H)
#define	PLSPRVL     2048        //缂栫爜鍣ㄦ瘡鍦堝厜鏍呮暟 娉�璇ュ�鏀瑰彉锛�.617994e-3瑕佹敼,鍒濆鍖朎Qep2Regs.QPOSMAX瑕佹敼锛乪ncoder pulses per revolution cpc
/*
//鐢垫満鍙傛暟----棰濆畾鐘舵�
#define MPR_Ls   	24.494882e-3	 	//瀹氬瓙鑷劅	--鍗曚綅H			锛堝疄闄呯浉鍊硷級
#define MPR_Lr   	15.889556e-3	 	//杞瓙鑷劅	--鍗曚綅H			锛堝疄闄呯浉鍊硷級
#define MPR_Lm   	19.02e-3	 	    //瀹氳浆瀛愪簰鎰�-鍗曚綅H
#define MPR_Rs   	0.106	     		//瀹氬瓙鐢甸樆	--鍗曚綅ohm		锛堝疄闄呯浉鍊硷級
#define MPR_Rr   	0.14995	    		//杞瓙鐢甸樆	--鍗曚綅ohm		锛堝疄闄呯浉鍊硷級
#define SIGMA	 	0.07053314			//(1-MPR_Lm*MPR_Lm/(MPR_Ls*MPR_Lr))	
#define	STAROTRTO	1.246504       		//瀹氳浆瀛愬彉姣�
#define	POLEPAIRES	2       			//鐢垫満鏋佸鏁�
*/
/*
//CPC鐢垫満鍙傛暟----棰濆畾鐘舵�褰掔畻鍒板畾瀛愪晶鍙傛暟
#define MPR_Ls   	18.154e-3	 	    //瀹氬瓙鑷劅	--鍗曚綅H
#define MPR_Lr   	18.3258e-3	 	    //杞瓙鑷劅	--鍗曚綅H
#define MPR_Lm   	17.87e-3	 	    //瀹氳浆瀛愪簰鎰�-鍗曚綅H
#define MPR_Rs   	0.007747	     	//瀹氬瓙鐢甸樆	--鍗曚綅ohm
#define MPR_Rr   	0.004175	    	//杞瓙鐢甸樆	--鍗曚綅ohm
#define SIGMA	 	0.040127			//(1-MPR_Lm*MPR_Lm/(MPR_Ls*MPR_Lr))	        
#define	STAROTRTO	0.5922       		//瀹氳浆瀛愬彉姣�
#define	STAROTRTO2	0.35070084       	//瀹氳浆瀛愬彉姣旂殑骞虫柟
#define	POLEPAIRES	2       			//鐢垫満鏋佸鏁�
*/

///-------------甯哥敤甯搁噺瀹忓畾涔�------------------------//
#define	SQRT3		1.73205081			//sqrt(3)
#define	SQRT3_2		0.8660254           //sqrt(3)/2
#define	SQRT3_3		0.57735027          //sqrt(3)/3
#define	SQRT2		1.41421356			//sqrt(2)
#define	PAI			3.1415926           //鍦嗗懆鐜�
#define TWOPAI      6.2831853           //2*PAI
#define PAI_2       1.5707963			//PAI/2
#define PAI_3       1.0471975			//PAI/3
#define TWOPAI_3    2.0943951			//2*PAI/3
#define TWOPAI_12   0.523598766			//2*PAI/12
#define IRQTOTE     27.51385e-3			//杞崲绯绘暟锛�Irq*涔樿绯绘暟鍐嶄箻缃戝帇ed=杞煩Te

//------------------------------寤舵椂鏃堕棿-------------------------------------------------
#define	DELAY_MAIN1			5										//涓�骇寰幆锛�ms
#define	DELAY_MAIN2			10										//浜岀骇寰幆锛�0ms
#define	DELAY_MAIN3			20										//涓夌骇寰幆锛�0ms
#define	DELAY_MAIN4			50										//鍥涚骇寰幆锛�0ms
#define	DELAY_MAIN5			100										//浜旂骇寰幆锛�00ms
#define	DELAY_MAIN6			1000									//鍏骇寰幆锛�000ms

//canopen
//#define	DELAY_CANOPENTX		13										//CANOPENTX锛�ms
#define	DELAY_CANOPENTX		6										//CANOPENTX锛�ms	120507
#define	DELAY_CANOPENOVER	1000									//CANOPENOVER锛�00ms,HEARTBEAT 2014-05-06LJD涓存椂淇敼CANopen
#define	DELAY_SCICANOPENOVER 250									//20090817
#define	DELAY_CANFAULT       10000									//CANOPENOVER锛氫笂鐢靛悗鍒ゆ柇CAN閫氳鏁呴殰

#define DELAY_AMUX          5      	//鎱㈤�AD
#define DELAY_UDCWAVE		1500	//鐩存祦鐢靛帇娉㈠姩瓒呮椂鏃堕棿

#define	DELAY_POWERON		5000  	//涓婄數鏃堕棿
#define	DELAY_PWMOUT		1000   	//绯荤粺浠庡惎鍔ㄦ爣蹇楃疆浣嶅埌鑴夊啿鍙戠敓鍏佽鏍囧織缃綅寤舵椂(ms)
#define	DELAY_NPRSTDBY		1000   	//NPR寰呮満---鏉垮瓙宸ヤ綔鐏參閫熼棯鐑�ms)
#define	DELAY_NPRRUN		100	   	//NPR宸ヤ綔---鏉垮瓙宸ヤ綔鐏揩閫熼棯鐑�ms)
#define	DELAY_MPRSTDBY		1000   	//MPR寰呮満---鏉垮瓙宸ヤ綔鐏參閫熼棯鐑�ms)
#define	DELAY_MPRRUN		100	   	//MPR宸ヤ綔---鏉垮瓙宸ヤ綔鐏揩閫熼棯鐑�ms)
#define	DELAY_FREQ			2000	   	//棰戠巼澶辫触鍏佽寤舵椂
#define	DELAY_CBFREQ		1000	//浠庝富鏂弽棣堥棴鍚堝埌鍒ゆ柇缃戦鏁呴殰鐨勫欢鏃讹紙ms锛�

#define	DELAY_FREQ2			200	   	//棰戠巼澶辫触鍏佽寤舵椂
#define	DELAY_OTSER			60000  	//瓒呮椂涓ラ噸寤舵椂(ms)
#define	DELAY_SCISPACE		10	   	//閫氳鎺ユ敹鍒板彂閫佺殑闂撮殧鏃堕棿(ms)
#define	DELAY_SCIOVER		5000	//閫氳鎺ユ敹/鍙戦�瓒呮椂鏃�ms)!!!!璋冭瘯鐣岄潰鍚庝慨鏀�0100125//have corected
//-----Protection-------
#define	DELAY_ESTOP  		6					//
#define	DELAY_CBTP		    6					//
#define DELAY_SWITCHDETECT	50		//寮�叧鎰忓鍔ㄤ綔鏁呴殰妫�祴寤舵椂10ms	110818
#define DELAY_DETECT		2000	//寮�叧鎰忓鍔ㄤ綔妫�祴鍒囨崲寤舵椂1s	110818
#define DELAY_EXFAULT       500 
#define DELAY_CBERROR       1000     //0.5s		110818 20110829HC
#define DELAY_MAINKERROR    1000     //0.5s		110818
#define DELAY_MAINFERROR    1000     //0.5s		110818
#define DELAY_STACERROR     1000     //0.5s		110818
#define DELAY_PREERROR      15000    //15s
#define DELAY_PGOVLOAD      10000    //10s
#define DELAY_QGOVLOAD      10000    //10s
#define DELAY_CBRESET       500    	 //0.5s
#define DELAY_SPEEDOUT      50       //50ms 20091022atzy 涓绘帶fastshutdown
#define DELAY_UACLV1        10000     //10s   20091027atzy
#define	DELAY_GFAULT		3000	//涓夌浉鐢垫祦涓嶅钩琛″埌鎺ュ湴鏁呴殰寤舵椂(ms)
#define DELAY_PHORDE        12000     //12s   201005atcpc
#define DELAY_ENCOFAULT     150     //150ms   201005atcpc

#define	DELAY_NPRTLOV		60000	//缃戜晶鐢垫劅瓒呮俯
#define DELAY_MPRTLOV		60000	//鏈轰晶鐢垫劅瓒呮俯
#define	DELAY_NSKIPTOV		10		//缃戜晶SKIIP瓒呮俯 systest
#define DELAY_MSKIPTOV		10		//鏈轰晶SKIIP瓒呮俯 systest

#define	DELAY_EE		    20					//eeprom寤惰繜鏃堕棿

#define	DELAY_ISTEADY0	    1000	 //RunCtrl缃戜晶鍋滄満缁欏畾寤舵椂1s
#define	DELAY_MPRSTEADY0    50     //RunCtrl缃戜晶鍋滄満缁欏畾寤舵椂0.05s
#define	DELAY_SENSZFSTDY    60000    //RunCtrl缃戜晶鍋滄満缁欐椂60s

//sysctl_start
#define	DELAY_STEADYFB	    2000	 //姝ｅ父鍚姩锛屾娴嬪埌Vdc绋冲畾鍦�100V鍒板厑璁告満渚ц剦鍐茬殑寤舵椂 2s
#define	DELAY_PRECOK        8000	 //姝ｅ父鍚姩锛岄鍏呯數鏃堕棿 8s
#define	DELAY_SERSTOP		2000	 //涓ラ噸鏁呴殰涓嬶紝鍙戝嚭鏂富鏂寚浠ゅ悗鍒板彂鍑烘柇瀹氬瓙鎺ヨЕ鍣ㄥ拰涓绘帴瑙﹀櫒鐨勫欢鏃�2s
#define	DELAY_ERRSTOP	    2000	 //鎺ユ敹鍒扮郴缁熷仠鏈烘寚浠ゅ悗锛屽欢鏃舵柇涓绘帴瑙﹀櫒 2s
#define	DELAY_EPWMSTOP	    500	 //姝ｅ父鍚姩锛屼竴鑸晠闅滃皝鑴夊啿鍚庡欢鏃舵柇涓绘柇鍐嶆柇鎺ヨЕ鍣�500ms  20110829
#define	DELAY_CBON	    	1000	 //姝ｅ父鍚姩锛岄棴鍚堜富鏂瑺鍘嬮摼鍒颁富鏂悎闂哥殑寤舵椂璁℃暟 1s
#define	DELAY_SYSOFF	    2000	 //椋庢満鍋滄満锛屾棤瑙嗚浆鐭╂寚浠わ紝鑷鍋滄満鍚庡欢鏃�s缃仠鏈虹粨鏉熸爣蹇�20120321
//sysctl_end  

#define	DELAY_RESET	        1000  	 //绯荤粺澶嶄綅寤舵椂锛岄槻姝㈣鎿嶄綔 2s
#define	DELAY_CLOSTACMD	    1000  	 //鍏佽鍚堝畾瀛愭帴瑙﹀櫒锛岄槻姝㈣鎿嶄綔 1s
#define	DELAY_NPRCMD	    1000  	 //涓婁綅鏈哄厑璁窷PR鍙戣剦鍐诧紝闃叉璇搷浣�1s
#define	DELAY_MPRCMD	    1000  	 //涓婁綅鏈哄厑璁窶PR鍙戣剦鍐诧紝闃叉璇搷浣�1s
#define	DELAY_EIN	    	1000  	 //琛旀崲顚庡垈娴﹂灚甯岊儝涔愬埉锜涘儺锟�s
#define	DELAY_SYSRUN	    1000  	 //涓婁綅鏈烘帶鍒剁郴缁熻繍琛�鐢垫満璇曢獙锛岄槻姝㈣鎿嶏拷1s
#define	DELAY_PREC	     	1000  	 //涓婁綅鏈烘帶鍒堕鍏呯數锛岄槻姝㈣鎿嶄綔 1s

#define	DELAY_QCAPSPDIN     120    	//杞瓙閫熷害娴嬫甯�20ms   20090817
#define	DELAY_QCAPDISTURB   100    	//杩炵画10娆℃娴嬭浆瀛愰�搴︿笉姝ｅ父鎶ユ晠闅�100ms  20090817
#define	DELAY_QEPCNTOK      1000    //杩炵画1s鏈彂鐢熶笂婧㈤敊璇�1s
#define	DELAY_QEPZDISTURB   1000    //杩炵画1s鍙戠敓Z淇″彿鎻愬墠鍒版潵琚共鎵伴敊璇� 1s

#define	DELAY_OCSEIN1     	250    	//20090817
#define	DELAY_OCSEIN2   	250    	//20090817
#define	DELAY_OCSSYSRUN1    250    	//20090817
#define	DELAY_OCSSYSRUN2   	250    	//20090817
#define	DELAY_MC_ACK		500  	 //500ms MagnetCurve2013-12-13

#define	DELAY_DATASAVE   	1800     //鏁呴殰鍙戠敓鍚庡欢鏃�.5s鍚庡仠姝㈠瓨鍌�0100203atbjtu
//LVRT
#define	DELAY_SCRIZERO	    15  	 //妫�祴寤舵椂0.5涓渶澶ц浆宸懆鏈�100ms/10Hz//201007BJTULVRT
#define	DELAY_MPWMSTOP	    0  	 	 //0ms
#define	DELAY_SCRIZERO2	    2  	 	 //2ms 20121103
#define	DELAY_MPWMRESTART	50  	 //50ms//201007BJTULVRT
#define	DELAYMPWM			0  	 	 //5ms
#define	DELAY_NPWMRESTART	50  	 //50ms//201007BJTULVRT
#define	DELAY_LVSTATE		2  	 	 //2ms
#define	DELAY_LVRCV			10  	 //40ms
#define	DELAY_LV_T1			625  	 //625ms
#define	DELAY_LV_T2			3000  	 //3000ms
#define	DELAY_LV_TEST		1000  	 //1000ms
#define	DELAY_SCRONDELAY	2000  	 //2s
#define	DELAY_LVFAULT1		200  	 //200ms
#define	DELAY_LVFAULT2		100  	 //100ms



//---------20121103atsp-----------
#define	DELAY_LVQWORKING	100  	 //100ms 20121103
#define	DELAY_PHICON		50  	 //50ms 
#define	DELAY_LVTEST2		1000  	 //1s 2013-12-6鏀逛负1s
#define	DELAY_LVUBALNCE		30  	 //30ms 201011LVRT
#define	DELAY_LVUTLV		500  	 //500ms 
#define	DELAY_LVMIDVAR		20  	 //20ms 

#define	DELAY_FREQRECV		10  	 //10ms 201011PLL
#define DELAY_IDCOV			300		//寤惰繜10ms妫�祴chopper鐢垫祦	201205LVRTatZB20120531
#define DELAY_IDCOVDELAY	1000	//寤惰繜1s妫�祴chopper鐢垫祦	BJTULVRT201204

#define	DELAY_VDSCRON		3		//3ms
#define	DELAY_VDSCROFF		2		//7ms

#define	DELAY_CHOPPER		100  	 //100ms 2013-12-6ZZJ  

//---------------------------鏁呴殰淇濇姢鍥炲樊鍊�----------------------------------------------
#define	SC_IAC_HW			2			//杈撳叆鐢垫祦淇濇姢鍥炲樊(鍩哄噯鐢垫祦鐨勭櫨鍒嗗�)
#define	SC_UDC_HW			20			//鐢靛帇淇濇姢鍥炲樊(V)
#define	SC_UAC_HW			20			//鐢靛帇淇濇姢鍥炲樊(V)
#define	SC_MSPD_HW			30			//杞�淇濇姢鍥炲樊(V) r/min
#define	SC_POWOROV_HW	    0	    	//鍔熺巼杩囪浇淇濇姢鍥炲樊(W) 0kW
#define	et_gate	    		50000	    //杩囪浇淇濇姢璁＄畻

//-----------------------------CANOPEN閫氫俊瀹忓畾涔�---------------------------------------------
//#define	SCICANOPENRXNUM		10										//CANOPENRX鏁版嵁鍖呭ぇ灏�
//#define	SCICANOPENTXNUM		18										//CANOPENTX鏁版嵁鍖呭ぇ灏�
#define CANOPENCOM_HEAD		0x7E									//CANOPEN鎶ュご
#define	SCICANOPENRXNUM		14										//CANOPENRX鏁版嵁鍖呭ぇ灏�20507
#define	SCICANOPENTXNUM		22										//CANOPENTX鏁版嵁鍖呭ぇ灏�20507
#define	SCICANOPENREADNUM	7										//CANOPENRD璇诲彇鎸囦护鏁版嵁鍖呭ぇ灏�20507
//-----------------------------CANOPEN閫氫俊瀹忓畾涔塏ORMAL----------------------------------------------
#define CAN_TEN  	  10000     //涓绘帶鎸囦护棰濆畾杞煩鍩哄噯鍊�(甯哥壍:1800r/min鏃禤=1560kW,Te=P*60/(n*2*pie)=8276 NM )
#define CAN_ANGLEN     90       //涓绘帶鎸囦护棰濆畾鏃犲姛鍥犳暟瑙掑害鍩哄噯鍊�
#define CAN_SPEED     1500      //涓绘帶鎸囦护棰濆畾杞�鍩哄噯鍊�
#define CAN_TEMP      100       //涓绘帶鎸囦护棰濆畾娓╁害鍩哄噯鍊�

//-----------------------------485閫氳----------------------------------------------
#define	SCI485NUM_RX		8										//485鏁版嵁鍖呭ぇ灏弇odbus

//#define UPSTART			    0x0064									//鎭㈠鍑哄巶鍙傛暟鐨勬牎楠岀爜
//#define SYSRESUME			0x0067									//鎭㈠鍑哄巶鍙傛暟鐨勬牎楠岀爜

//涓婁綅鏈哄彂閫佸懡浠�
#define COM_RDDO			0x0001									//璇诲彇鍔熻兘鐮�璇诲彇涓嬩綅鏈篍EPROM涓殑鍔熻兘鐮佸�鍐欏叆鍒颁笂浣嶆満EEPROM涓�
#define COM_RDAO			0x0003									//璇诲彇鍔熻兘鐮�璇诲彇涓嬩綅鏈篍EPROM涓殑鍔熻兘鐮佸�鍐欏叆鍒颁笂浣嶆満EEPROM涓�
#define COM_WRDO			0x0005									//淇敼鍔熻兘鐮�淇敼涓嬩綅鏈篟AM涓殑鍔熻兘鐮佸�)
#define COM_WRAO			0x0006									//淇敼鍔熻兘鐮�淇敼涓嬩綅鏈篟AM涓殑鍔熻兘鐮佸�)
#define COM_RDRAM			0x0046									//璇诲彇exRAM鍔熻兘鐮�20100203atbjtu)

//------------------------------CANOPEN-------------------------------------------------------------
//CANOPEN涓婁綅鏈虹姸鎬佸瓧
#define COM_EIN			    0x0001									//BIT0
#define COM_NPREIN			0x0002									//BIT1
#define COM_SYSRUN			0x0004									//BIT2
#define COM_PGMODE			0x0010									//BIT4
#define COM_QGMODE			0x0020									//BIT5
#define COM_OCSRESET		0x0080									//BIT7
#define COM_HEARTBEAT1		0x8000									//BIT15
//CANOPEN鍙嶉涓婁綅鏈虹殑鍙樻祦鍣ㄧ姸鎬佸瓧1
#define COM_NPRREADY	    0x0001									//BIT0
#define COM_NPRON			0x0002									//BIT1
#define COM_READYGENERATION	0x0004									//BIT2
#define COM_FAILURE			0x0008									//BIT3
#define COM_SPEEDINRANGE	0x0010									//BIT4
#define COM_FAILUREA		0x0020									//BIT5
#define COM_FAILUREB		0x0040									//BIT6
#define COM_TOOCOLD		    0x0080									//BIT7
#define COM_PLIM	        0x0100									//BIT8
#define COM_QLIM			0x0200									//BIT9
#define COM_GRIDFAILURE 	0x0400									//BIT10
#define COM_CROWBAR			0x0800									//BIT11
#define COM_VLIM        	0x1000									//BIT12
#define COM_HEARTBEAT2		0x8000									//BIT15

#define COM_NPRREADY_NOT	    0xFFFE								//BIT0
#define COM_NPRON_NOT			0xFFFD								//BIT1
#define COM_READYGENERATION_NOT	0xFFFB								//BIT2
#define COM_FAILURE_NOT			0xFFF7								//BIT3
#define COM_SPEEDINRANGE_NOT	0xFFEF								//BIT4
#define COM_FAILUREA_NOT		0xFFDF								//BIT5
#define COM_FAILUREB_NOT		0xFFBF								//BIT6
#define COM_TOOCOLD_NOT		    0xFF7F								//BIT7
#define COM_PLIM_NOT	        0xFEFF								//BIT8
#define COM_QLIM_NOT			0xFDFF								//BIT9
#define COM_GRIDFAILURE_NOT 	0xFBFF								//BIT10
#define COM_CROWBAR_NOT			0xF7FF								//BIT11
#define COM_VLIM_NOT        	0xEFFF								//BIT12
#define COM_HEARTBEAT2_NOT		0x7FFF								//BIT15
//CANOPEN鍙嶉涓婁綅鏈虹殑鍙樻祦鍣ㄧ姸鎬佸瓧2
#define COM_ILIM			0x0001									//BIT0
#define COM_HEATSINKT		0x0002									//BIT1
#define COM_ESTOP			0x0004									//BIT2
#define COM_CBTRIP			0x0010									//BIT4
#define COM_POWLIM			0x0040									//BIT6
#define COM_VOLDIP			0x0100									//BIT8
#define COM_CBCLOSED		0x8000									//BIT15	 20090815

#define COM_ILIM_NOT		0xFFFE									//BIT0
#define COM_HEATSINKT_NOT	0xFFFD									//BIT1
#define COM_ESTOP_NOT		0xFFFB									//BIT2
#define COM_CBTRIP_NOT		0xFFEF									//BIT4
#define COM_POWLIM_NOT		0xFFBF									//BIT6
#define COM_VOLDIP_NOT	    0xFEFF									//BIT8
#define COM_CBCLOSED_NOT	0x7FFF									//BIT15 20090815

//-------------------------AD銆丏A杞崲鍙婃暟鎹鍙栫殑鎺у埗-----------------------------------------
#define	AD8364_CONVERT		1										//8364寮�杞崲
//#define	AD1544_CONVERT		2										//1544寮�杞崲
//#define	DA7614_CONVERT		4										//7614寮�杞崲
//ad
#define AD_ASTART		    ((Uint16 *)0x100000)						//鐗囧AD鐨勬暟鑽诲鈭堟鍒傦拷
#define AD_BSTART		    ((Uint16 *)0x110000)						//鐗囧AD鐨勬暟鎹鍙栭鍦板潃
#define AD_CSTART		    ((Uint16 *)0x120000)						//鐗囧AD鐨勬暟鎹鍙栭鍦板潃
#define AD_DA_CTRL		    ((Uint16 *)0x130000)						//鐗囧AD,DA鐨勬帶鍒跺瓧鑺傚湴鍧�
//da
#define DA_ADD0				((Uint16 *)0x1B0000)						//杈撳嚭鍦板潃0
#define DA_ADD1				((Uint16 *)0x1B0001)						//杈撳嚭鍦板潃1
#define DA_ADD2				((Uint16 *)0x1B0002)						//杈撳嚭鍦板潃2
#define DA_ADD3				((Uint16 *)0x1B0003)						//杈撳嚭鍦板潃3

//External RAM 20091109atzy
#define BANK_RAMSTART		((Uint16 *)0x200000)						//鐗囧RAM棣栧湴鍧�INTF zone 7
#define BANK_RAMEND			((Uint16 *)0x21E848)						//鐗囧RAM灏惧湴鍧�INTF zone 7 end at 125000
#define ERROR_RAMSTART		((Uint16 *)0x21FBD0)						//鐗囧RAM棣栧湴鍧�INTF zone 7 start at 130000
#define ERROR_RAMEND		((Uint16 *)0x23E418)						//鐗囧RAM灏惧湴鍧�INTF zone 7 end at 255000
#define RAM_BIAS			5000										//=2s/(0.4ms/point)=5000points/variable
Uint16  BANK_RAMDATA_POS;						    					//瀛樺偍鍙橀噺鐨勫瓨鍌ㄧ偣浣嶇疆[0,4999]
Uint16  ERROR_RAMDATA_POS;						    					//瀛樺偍鍙橀噺鐨勫瓨鍌ㄧ偣浣嶇疆[0,4999]
#define RAM_SEGMENT			1000											//姣忎釜娉㈠舰姣忔鍙戦�鍒嗘鎵撳寘闀垮害


//----------------------------杈撳叆杈撳嚭鍦板潃瀹氫箟--------------------------------------------
#define IN1_ADDR			((Uint16 *)0x140000)	//杈撳叆鍦板潃1
#define IN2_ADDR			((Uint16 *)0x150000)	//杈撳叆鍦板潃2
#define IN3_ADDR			((Uint16 *)0x160000)	//杈撳叆鍦板潃3
#define IN4_ADDR			((Uint16 *)0x170000)	//杈撳叆鍦板潃4

#define OUT1_ADDR			((Uint16 *)0x180000)	//杈撳嚭鍦板潃2
#define OUT2_ADDR			((Uint16 *)0x190000)	//杈撳嚭鍦板潃3
#define OUT3_ADDR			((Uint16 *)0x1A0000)	//杈撳嚭鍦板潃3
#define OUT4_ADDR			((Uint16 *)0x1C0000)	//杈撳嚭鍦板潃4,涓庢參閫烝D鏈夊叧

//--------------------------------SPI閫氳瀹忓畾涔�------------------------------------------
#define	SPINUM				4										//SPI鍙ｅ彂閫�鎺ユ敹鏁版嵁閲�

//-----------------------------------鏃堕挓--------------------------------------------------
#define	HSPCLK				75      		//楂橀�鍩哄噯鏃堕挓棰戠巼(Hz)
#define	LSPCLK				37500000		//浣庨�鍩哄噯鏃堕挓棰戠巼(Hz)

//--------------------------------鏍囧織浣嶅畾-----------------------------------------------
//flag[0]鏄剧ず鍙婅瀹氭爣
#define	SL_DISPLAY0			0x00			//LED鏄剧ず0
#define	SL_DISPLAY1			0x01			//LED鏄剧ず1
#define	SL_DISPLAY2			0x02			//LED鏄剧ず2
#define	SL_DISPLAY3			0x03			//LED鏄剧ず3
#define	SL_DISPLAY4			0x04			//LED鏄剧ず4
#define	SL_DISPLAY5			0x05			//LED鏄剧ず5
#define	SL_DISPLAY6			0x06			//LED鏄剧ず6
#define	SL_DISPLAY7			0x07			//LED鏄剧ず7
#define SL_RAMERRORSAVE     0x08            //=1澶栭儴RAM鏁呴殰閮ㄥ垎閿佸瓨鏍囧織
#define SL_RAMBANKSAVE      0x09            //=1澶栭儴RAM鏁呴殰閮ㄥ垎閿佸瓨鏍囧織
#define	SL_TRIG_ERRDSAVE    0x0A      		//瑙﹀彂澶栭儴RAM鏁版嵁杞瓨20091109atzy
#define	SL_PC_ERRDATACLR    0x0B      		//瑙﹀彂澶栭儴RAM鏁版嵁閲婃斁 PCmodbus20100305
#define	SL_PC_ERRDATASAVE   0x0C      		//PC瑙﹀彂澶栭儴RAM鏁版嵁閿佸瓨 PCmodbus20100308
#define SL_PC_BANKDATASAVE  0x0D            //PC鎸囦护澶栭儴RAM鏄剧ず鏁版嵁閿佸瓨 PCmodbus20100308
#define	SL_MC_OK   			0x0E      		//鍔辩鏇茬嚎MagnetCurve2013-12-13
#define SL_MC_FAIL          0x0F    		//鍔辩鏇茬嚎MagnetCurve2013-12-13

//#define	SL_STA_PHORDE   	0x0E      		//TEST
//#define SL_ROT_PHORDE  		0x0F            //
  
//flag[1]涓茶閫氫俊鐩稿叧鏍�eeprom鐩稿叧鏍�
#define SL_TX		    	0x10			//1=琛ㄧずsci姝ｅ湪鍙戦�
#define SL_RX		    	0x11			//1=琛ㄧずsci鎺ユ敹瀹屾垚寤舵椂涓�
#define SL_RESUME    		0x12			//1=鎭㈠鍑哄巶鍙傛暟杩涜涓�
#define SL_HEADOK			0x13			//1=鏈抚鏁版嵁鎶ュご姝ｇ‘
#define SL_SETRTIMER		0x14			//1=闇�鏍℃瀹炴椂鏃堕挓
#define SL_EE_NOACK			0x15
#define	SL_EE_FAIL			0x16			//=1eeprom鍐欏叆閿欒
#define SL_CODEOK			0x17			//=1鍔熻兘鐮佹牎楠屽畬姣�
#define SL_EEASK_INI		0x18			//=涓婁綅鏈鸿姹俥eprom鎭㈠鍑哄巶鍙傛暟
#define SL_EEASK_MCODE		0x19			//=1瀛樺湪淇敼鍔熻兘鐮佽姹�
#define SL_EEASK_ERRSAVE	0x1A			//=1瀛樺湪淇濆瓨鏁呴殰淇℃伅璇锋眰
#define SL_EEBUSY_INI		0x1B			//=1鎭㈠鍑哄巶鍙傛暟杩涜涓�
#define SL_EEBUSY_MCODE		0x1C			//=1淇敼鍔熻兘鐮佽繘琛屼腑
#define SL_EEBUSY_ERRSAVE	0x1D			//=1淇濆瓨鏁呴殰淇℃伅杩涜涓�
#define SL_TXLONGDATA		0x1E			//=1鍙戦�闀挎暟鎹繘琛屼腑

//#define SL_PHO_FH			0x1F			//=1TEST
#define SL_CANOPENTX_FLAG	0x1F			//120507
	
//flag[2]QEP鐩稿叧鏍囧織浣�鍙婃晠闅滄爣蹇椾綅
#define SL_QEPPCO			0x20			//=1 QEP璁℃暟涓婃孩鏁呴殰
#define SL_QCAPDISTURB		0x21			//=1 QEP鑴夊啿鍙楀埌骞叉壈鏁呴殰 杩炵画10娆¤鍙栧潎涓嶅湪姝ｇ‘鑼冨洿鍐�20090804cpc
#define	SL_QEPZDISTRUB	    0x22     	    //=1 QEP Z淇″彿鍙楀埌骞叉壈锛岃繛缁�s鍐呴敊璇氨鎶ユ晠闅�  20090804cpc
#define SL_ENCODFAULT		0x23			//=1 QEP鏁呴殰(缂栫爜鍣ㄦ晠闅�
#define	SL_QEPPCDE          0x24      		//缂栫爜鍣ㄨ浆鍚戞敼鍙橀敊璇�A鎴朆淇″彿娑堝け
#define	SL_QCAPSPDIN        0x25      		//QEP鐨凜AP鐢佃矾鑳藉姝ｇ‘妫�祴 qcap speed in
#define	SL_SPEED_HIGH       0x26      		//楂樿浆閫熷尯閲囩敤QCLK128鍒嗛锛屼綆杞�閲囩敤8鍒嗛
//flag[2]鎺ヨЕ鍣ㄦ晠闅滄爣蹇椾綅
#define SL_ERROR_CB        	0x27        	//=1涓绘柇鏈夋晠闅�
#define SL_ERROR_MAINF   	0x28         	//=1涓绘护娉㈠櫒鏁呴殰
#define SL_ERROR_MAINK     	0x29         	//=1涓绘帴瑙﹀櫒鏁呴殰
#define SL_ERROR_STAC		0x2A         	//=1瀹氬瓙鎺ヨЕ鍣ㄦ晠闅�
#define SL_ERROR_PRE       	0x2B         	//=1棰勫厖鐢垫敹锟�
#define SL_MSPOUT        	0x2C         	//=1杞�瓒呭嚭鑼冨洿鏁呴殰
#define SL_SYNFAIL        	0x2D         	//=1瀹氬瓙鍚屾骞剁綉澶辫触鏁呴殰
#define SL_STEADYGV			0x2E			//=1Vdc缁欏畾绋冲畾
#define SL_STEADYFB			0x2F			//=1Vdc鍙嶉鐢靛帇绋冲畾

//flag[3]鐘舵�鏍�
#define SL_POWERON			0x30			//=1绯荤粺涓婄數瀹屾垚
#define SL_WARNING			0x31			//=1鎶ヨ
#define SL_OFFCB			0x32			//=1鏂富鏂�
//#define SL_SOFT				0x33			//=1缂撴參鍋滄
#define SL_DL_RESET			0x33			//=1寤舵椂鍏佽澶嶄綅
#define SL_SHUT				0x34			//=1绱ф�鍋滄
#define SL_NRCVR			0x35			//=1鏁呴殰涓嶈兘鎭㈠
#define SL_DRCVR			0x36			//=1鏁呴殰寤舵椂鎭㈠
#define SL_IRCVR			0x37			//=1鏁呴殰绔嬪嵆鎭㈠
#define SL_CNT				0x38			//=1璁″叆鏁呴殰娆℃暟
#define SL_OTSER			0x39			//=1鏁呴殰瓒呮椂涓ラ噸
#define SL_SAVE				0x3A			//=1鏁呴殰闇�瀛樺偍
#define	SL_NO_RESET        	0x3B      		//=1绂佹澶嶄綅鏍囧織浣�
#define SL_IUBLNCE1     	0x3C			//1=鐢电綉渚ф紡鐢垫祦瓒呴檺
#define SL_IUBLNCE2      	0x3D			//1=鏈轰晶婕忕數娴佽秴闄�
#define SL_GFAULT1			0x3E			//1=鐢电綉渚ф帴鍦版晠闅�
#define SL_GFAULT2		    0x3F			//1=鏈轰晶鎺ュ湴鏁呴殰

//flag[4]鏁呴殰鏍�
#define SL_ERROR			0x40			//=1绯荤粺鏁呴殰
#define SL_ERRSTOP			0x41			//=1绯荤粺涓�埇鏁呴殰
#define	SL_SERIESTOP        0x42      		//=1绯荤粺涓ラ噸鏁呴殰
#define	SL_PDPINTA			0x43			//=1鍔熺巼椹卞姩淇濇姢A
#define	SL_PDPINTB			0x44			//=1鍔熺巼椹卞姩淇濇姢B
#define	SL_UDCWAVE			0x45			//=1涓棿鐢靛帇涓嶇ǔ瀹氾紝瓒呭嚭580V鍜�20V
#define SL_HIA1			    0x46			//=1缃戜晶鍙樻祦鍣ˋ鐩哥‖浠惰繃娴�
#define SL_HIB1			    0x47			//=1缃戜晶鍙樻祦鍣˙鐩哥‖浠惰繃娴�
#define SL_HIC1			    0x48			//=1缃戜晶鍙樻祦鍣–鐩哥‖浠惰繃娴�
#define SL_HIA2		 	   	0x49			//=1鐢垫満渚у彉娴佸櫒A鐩哥‖浠惰繃娴�
#define SL_HIB2		   	 	0x4A			//=1鐢垫満渚у彉娴佸櫒B鐩哥‖浠惰繃娴�
#define SL_HIC2		   	 	0x4B			//=1鐢垫満渚у彉娴佸櫒C鐩哥‖浠惰繃娴�
#define SL_SIAC1		    0x4C			//=1缃戜晶鍙樻祦鍣ㄨ蒋浠惰繃娴�
#define SL_SIAC2		    0x4D			//=1鐢垫満渚у彉娴佸櫒杞欢杩囨祦
#define SL_SUDCOV			0x4E			//=1涓棿鐩存祦姝ｈ繃鍘�
#define SL_UACLV2			0x4F			//=1缃戝帇鐬棿璺岃惤鏁呴殰LVRT 201007BJTULVRT

//flag[5]鏁呴殰鏍�
#define SL_UACOV1			0x50			//=1缃戝帇杞欢杩囧帇
#define SL_UACLV1			0x51			//=1缃戝帇杞欢娆犲帇
#define SL_PGOV				0x52			//=1鍙樻祦鍣ㄦ湁鍔熷姛鐜囪繃杞�
#define SL_QGOV				0x53			//=1鍙樻祦鍣ㄦ棤鍔熷姛鐜囪繃杞�
#define	SL_GRDFQE			0x54			//=1缃戜晶棰戠巼妫�祴鏈夎
#define SL_FE1			    0x55			//=1缃戜晶棰戠巼鏁呴殰
#define	SL_PDPASERIES		0x56			//=1缃戜晶涓ラ噸鏁呴殰
#define SL_PDPBSERIES		0x57			//=1鐢垫満渚т弗閲嶆晠闅�
#define SL_HUDCOV			0x58			//=1纭欢杩囧帇鏁呴殰
#define SL_HIACOV1			0x59			//=1缃戜晶浜ゆ祦纭欢淇濇姢杩囨祦鏁呴殰
#define SL_HIACOV2			0x5A			//=1鐢垫満渚т氦娴佺‖浠朵繚鎶よ繃娴佹晠闅�
#define SL_CBTRIP 			0x5B			//=1涓绘柇鑴辨墸鎴栬�涓绘帶鏂紑涓绘柇鏁呴殰
#define	SL_EXFAIL		    0x5C			//=1鍙樻祦鍣ㄥ閮ㄧ‖浠舵晠闅�
#define	SL_ESTOP			0x5D			//=1澶栭儴绱ф�鍋滄満鏁呴殰
#define SL_PHORDE		    0x5F            //=1鐩稿簭姝ｅ父

//flag[6]杩愯鏂瑰紡
#define SL_ENPCOPER			0x60			//鎺у埗妯″紡锛�=PC鎺у埗锛�=CAN鎺у埗			modbus2010
#define SL_OPERATION		0x61			//杩愯妯″紡锛�=缃戜晶鍗曠嫭杩愯 0=鑳岄潬鑳岃繍琛�modbus2010
#define	SL_NPR_START		0x62			//缃戜晶鍙樻祦鍣ㄨ繍琛屾寚浠�1=杩愯
#define	SL_MPR_START		0x63			//鏈轰晶鍙樻祦鍣ㄨ繍琛屾寚浠�1=杩愯
#define	SL_NPR_RUN			0x64			//=1缃戜晶鍙樻祦鍣ㄥ伐浣滃厑璁�
#define	SL_MPR_RUN			0x65			//=1鏈轰晶鍙樻祦鍣ㄥ伐浣滃競锟�
#define	SL_NPR_RUNING		0x66			//=1缃戜晶鍙樻祦鍣ㄦ鍦ㄥ伐锟�
#define	SL_MPR_RUNING		0x67			//=1鏈轰晶鍙樻祦鍣ㄦ鍦ㄥ伐浣�
#define SL_NPR_PWMOUT       0x68            //=1缃戜晶鑴夊啿宸茬粡浣胯兘鏍囧織浣�骞朵笖淇濊瘉Enepwmio_NPR()鍙兘杩愯涓�
#define SL_MPR_PWMOUT       0x69            //=1鏈轰晶鑴夊啿宸茬粡浣胯兘鏍囧織浣�骞朵笖淇濊瘉Enepwmio_MPR()鍙兘杩愯涓�
#define SL_RUN				0x6A			//=1绯荤粺璇碉拷
#define SL_CONFIGPWM		0x6B			//=1PWM鑴夊啿閰嶇疆瀹屾垚鏍囧織浣�顥祇nfigPwm()鍙兘杩愯涓�
#define SL_FAN_WORK         0x6C			//=1瑕佹眰鍔熺巼椋庢墖寮�宸ヤ綔
#define SL_CHARGEOK			0x6D			//=1棰勫厖鐢靛畬鎴�
//#define SL_SENSZFSTDY       0x6E            //=1浼犳劅鍣ㄩ浂婕傛护娉㈢粨鏉�
#define SL_UNBALANCE       	0x6E            //=1鐢电綉涓嶅钩琛℃爣蹇椾綅 20121103
#define SL_SPEED_IN_RANGE	0x6F			//=1杞�鍦ㄨ寖鍥翠互鍐�
								
//flag[7]杈撳嚭鏍�,IO杈撳嚭   0x180000          //鐢靛櫒杈撳嚭锛�1 杈撳嚭DC24V
#define _OUT1_DATA			flag[7]	
#define CL_CBLVC            0x70         	//=0涓绘柇鏂紑鎸囦护P5.5
#define CL_CBON   			0x71			//=1瑕佹眰鍚堜富鏂璓5.6
#define CL_PRE   			0x72			//=1瑕佹眰鍚堥鍏呯數P5.7
#define	CL_MAINK    		0x73			//=1瑕佹眰鍚堟帶鍒朵富鎺ヨЕ鍣ㄥ拰婊ゆ尝鍣ㄥ櫒P5.8
#define CL_STATORK		    0x74			//=1瑕佹眰鍚堟帶鍒跺畾瀛愭帴瑙﹂睂5.9
#define CL_CBFCON           0x75			//=1瑕佹眰涓绘柇娆犲帇閾鹃棴鍚堬紝0=涓绘柇娆犲帇閾炬柇寮�5.10
#define CL_FANWORK	        0x76			//=1瑕佹眰鍔熺巼椋庢墖杩愯P5.11
//#define CL_SAVEC	        0x77			//=1姝ｅ父,瀹夊叏閾鹃棴鍚圥5.12 20110829
#define CL_ZKLVRT	        0x77			//=1鍙戠敓缃戝帇璺岃惤锛屽彂缁欎富鎺�4V淇″彿20121107

//flag[8]杈撳嚭鏍�         0x190000           //缁х數鍣ㄨ緭鍑猴紝=1 杈撳嚭AC220V
#define _OUT2_DATA			flag[8]				
#define CL_RELAY8      		0x80			//澶囩敤
#define CL_CHOPTEST        	0x81			//鏂╂尝娴嬭瘯 2013-12-6ZZJ
#define SL_WATCHDOG			0x82            //DSP杞欢鐪嬮棬鐙�20100401at27
//#define SL_SWITCHDETECT    	0x84         	//=1妫�祴鎰忚垱顖岋拷		110818
#define CL_CHOPEN			0x83			//enable chopper

//--------浠ヤ笅鏍囩枤鐜灅娑戣Н顑熻瘬鍕樻洓锟�------------------------------------------
#define SL_ERRSTOP_S1		0x84            //涓�埇鏁呴殰姝ラ鏍囧織浣�0110829
#define SL_SWITCHDETECT    	0x85         	//=1妫�祴鎰忚垱顖岋拷		110818
#define SL_QEPPHE    		0x86         	//=1鐢垫満鍙嶈浆鎴朅B鍙嶆帴鏁呴殰 20110829HC
#define SL_SYSOFF    		0x87         	//=1椋庢満姝ｅ父鍋滄満鏃惰浆閫熻繃浣庯紝涓嶅啀鎺ユ敹涓绘帶杞煩鎸囦护锛岃嚜琛屽仠鏈�20120321
#define SL_IDCOV    		0x88         	//=1涓棿鐩存祦鏂╂尝杞欢鐢垫祦杩囨祦鍒ゆ柇-BJTULVRT201204
#define SL_LV_SYNCON    	0x89         	//=1鏈轰晶鍔ㄦ�PI鎺у埗鏍囧織浣�BJTULVRT201204
#define SL_LV_PHICON    	0x8A         	//=1鏈轰晶鏈夋簮纾侀摼琛板噺鎺у埗鏍囧織浣�BJTULVRT201204
#define SL_CHOPPEREN		0x8B			//=1鏂╂尝鍣ㄤ娇鑳�	20120228	BJTULVRT201204
#define SL_LV_SCRKEEPON		0x8C			//=1crowbar涓�洿寮��鏍囧織20120602
#define SL_LV_VDSCRON		0x8D			//=1鐢靛帇璺岃惤瑙﹀彂SCR 20121203
#define SL_LV_SCROFF1		0x8E			//=1 35%涓嶅绉板叧SCR 20121210
#define SL_LV_SCROFF2		0x8F			//=1 50%涓嶅绉板叧SCR 20121210

//flag[15]杈撳嚭鏍�         0x1A0000          //鎱㈤�AD鍦板潃杈撳嚭
#define _OUT3_DATA			flag[15]									
#define SL_PHASEA			0xF0		     //					
#define SL_PHASEB			0xF1             //
 
Uint16   _OUT4_DATA;		//璇ユ爣蹇椾綅鏃犵敤鏀逛负瀹忓畾涔�0130222

//flag[11]杈撳嚭鏍�         0x1C0000          //AD鍧�緭鍑�
/*#define _OUT4_DATA			flag[11]									
#define SL_LSADA0			0xB0		     //A0						
#define SL_LSADA1			0xB1             //A1
#define SL_LSADA2			0xB2             //A2
#define SL_LSADA3			0xB3	         //A3							
*/
//flag[11]LVRT鐩稿叧鏍囧織浣�20130222
#define SL_LV_RECMSTOP			0xB0			//=1鎭㈠鏃跺埢涓诲姩灏佽剦鍐�20130124
#define SL_LV_ZDNSTOP			0xB1			//=1璺岃惤鏃跺埢缃戜晶涓诲姩灏佽剦鍐�20130202
//#define SL_LV_XNZKKZ			0xB2			//=1铏氭嫙闃绘姉鎺у埗鏈熼棿	20130202
#define SL_LV_STRICTLV			0xB2			//=1涓ユ牸LV鍖洪棿	20130222
#define SL_LV_RECNSTOP			0xB3			//=1鎭㈠鏃跺埢涓诲姩灏佽剦鍐�20130206
#define SL_LV_ZDMSTOP			0xB4			//=1璺岃惤鏃跺埢鏈轰晶涓诲姩灏佽剦鍐�20130221
#define SL_LV_SCRDONE			0xB5			//=1 鎶曞叆scr涓�20130221
#define SL_LV_CLRERRAM			0xB6			//=1 娓呴櫎LV璇Е鍙戞尝褰�0130306
#define SL_CANOPENHEAD			0xB7			//=1 鏀跺埌鎶ュご	20130801
#define SL_ENCODEPOS_OK			0xB8			//=1缂栫爜鍣ㄤ綅缃娴嬪畬鎴�20130801
#define SL_ECPOSSEARCH			0xB9			//=1缂栫爜鍣ㄤ綅缃牎楠岃繃 	20130801


//flag[9]杈撳叆鏍�2
#define _IN12_DATA			flag[9]			//鍙樻祦鍣ㄥ竷顠炲埡顑掕牏锟�
//---------------------0x140000----------------------------------------------------------------------------
#define SL_IN1_CBSTS 			0x90			//=1 涓绘柇澶勪簬闂悎鐘舵�顑嘝4.1
#define SL_IN1_CBRESET			0x91			//=1 妫�祴鍒伴鍖绢�绗鹃灚锜丒SET鎸囦护(闇�寤舵椂涓�鏃堕棿鍚庢墠鑳藉悎涓绘柇)锛孭4.2
#define SL_IN1_STATORK			0x92			//=1 瀹氬瓙鎺ヨЕ鍣ㄥ浜庡悎闂告�锛孭4.3
#define SL_IN1_MIANK   			0x93			//=1 涓绘帴瑙﹀櫒澶勪簬鍚堥椄鐘额偩鐞�.4
#define SL_IN1_MIANFILTER		0x94			//=1 涓绘护娉㈠櫒澶勪簬鍚堥椄鐘舵�锛孭4.5
#define SL_IN1_EXFAULTOK	   	0x95			//=1 澶栭儴鏁呴殰閾炬甯革紝0=鏁呴殰鍙戠敓	P4.6顐�
#define SL_IN1_MIANFAN	    	0x96	        //=1 鍔熺紒顚ゎ悳锛冿拷=瓒呮俯闅�  P4.7
#define SL_IN1_EXESTOP	        0x97			//=1 澶栭儴鎬ュ仠鏁呴殰  鍙樻祦鍣ㄦ煖涓婄揣鎬ュ仠顙跨銈拌仾锟� P4.8	090815
//---------------------0x150000---------------------------------------------------------------------------	
#define SL_IN2_IOVA1			0x98			//=1 缃戜晶A鐩�SKiiP鏁呴殰(杩囨祦鎴栬�瓒呮俯)
#define SL_IN2_IOVB1			0x99			//=1 缃戜晶B鐩�SKiiP鏁呴殰(杩囨祦鎴栬�瓒呮俯)
#define SL_IN2_IOVC1			0x9A			//=1 缃戜晶C SKiiP鏁呴殰(杩囨祦鎴栬�瓒呮俯)
#define SL_IN2_TAOV			    0x9B			//=1 缃戜晶SKiiP瓒呮俯鏁呴殰
#define SL_IN2_IOVA2			0x9C			//=1 鐢垫満渚鐩窼KiiP鏁呴殰(杩囨祦鎴栬�瓒呮俯锛�
#define SL_IN2_IOVB2			0x9D			//=1 鐢垫満渚鐩�SKiiP鏁呴殰(杩囨祦鎴栬�瓒呮俯)
#define SL_IN2_IOVC2			0x9E			//=1 鐢垫満渚鐩�SKiiP鏁呴殰(杩囨祦鑰呰秴娓�
#define SL_IN2_TBOV				0x9F			//=1 鐢垫満渚KiiP瓒呮俯鏁呴殰


//flag[10]杈撳叆鏍�4      0x160000
#define _IN34_DATA			flag[10]			//鎺у埗鏉跨‖浠朵繚鎶ゆ晠闅滃弽棣�
//-----------------------------------------------------------------------------------------------				
#define SL_IN3_VDCOV			0xA0			//=1 鐩存祦鐢靛帇杩囧帇
#define SL_IN3_NPRIOV			0xA1			//=1 缃戜晶浜ゆ祦纭欢淇濇姢杩囨祦鏁呴殰
#define SL_IN3_MPRIOV			0xA2			//=1 鐢垫満渚т氦娴佺‖浠朵繚鎶よ繃娴佹晠闅�

#define SL_IN3_CBTRIP		    0xA3			//=1 涓绘柇杩囨祦鑴辨墸鏁呴殰  P4.9   20090816
//#define SL_IN3_OCS_NPRSTART		0xA4			//=1 涓婁綅鏈哄厑璁稿彂缃戜晶鑴夊啿  鎿嶄綔鏉夸俊鍙凤紝椋庡満娌＄敤
//#define SL_IN3_OCS_MPRSTART		0xA5			//=1 涓婁綅鏈哄厑璁稿彂鏈轰晶鑴夊啿  鎿嶄綔鏉夸俊鍙凤紝椋庡満娌＄敤
#define SL_IN3_IOVDC			0xA6			//=1 dc-link chopper errror 20120228atbjtu	BJTULVRT201204
//娉ㄦ剰锛氱敤楂�浣嶆椂锛岃緭鍏ヨ祴鍊间細娓呴浂20130222atzb

//flag[12]涓绘帶閫氳鍙奝C鎸囦护鏍囧織浣�
#define SL_OCS_NPREIN       0xC0            //=1涓绘帶瑕佹眰鍙樻祦鍣ㄧ綉渚у崟鐙棤鍔熷苟缃戣繍琛�
#define SL_OCS_EIN          0xC1            //=1涓绘帶鍙戣繃鏉ョ殑绯荤粺鍚姩淇″彿  bit0 鍚堜富鏂矾鍣�
#define SL_OCS_SYSRUN    	0xC2			//=1涓绘帶鍙戣繃鏉ョ殑鍙樻祦鍣ㄥ惎鍔ㄤ俊鍙� bit2 寮�棰勫厖鐢电洿鑷冲畾瀛愭帴瑙﹀櫒闂悎
#define SL_CBCLOSED    	    0xC3			//=1鍙嶉涓绘帶锛屼富鏂凡缁忛棴鍚�
#define SL_MPR_SYNOK        0xC4            //=1鏈轰晶鍚屾骞剁綉瀹屾垚鏍囧織浣�
#define SL_PGOV_COM         0xC5            //=1鏈夊姛鍔熺巼瓒呭嚭闄愬埗锛岄�鐭ヤ富鎺�鎸佺画10s鍚庡彉娴佸櫒浼氭姤鏁呴殰
#define SL_QGOV_COM         0xC6            //=1鏃犲姛鍔熺巼瓒呭嚭闄愬埗锛岄�鐭ヤ富鎺�鎸佺画10s鍚庡彉娴佸櫒浼氭姤鏁呴殰
#define SL_OCS_PREC			0xC7			//=1PC鎺у埗棰勫厖鐢垫寚浠�
#define SL_OCS_NPRSTART     0xC8            //=1PC鎺у埗瑕佹眰NPR鍙戣剦鍐�
#define SL_OCS_MPRSTART     0xC9            //=1PC鎺у埗瑕佹眰MPR鍙戣剦鍐�
#define SL_OCS_RESET        0xCA            //=1涓绘帶鍙戣繃鏉ョ殑鏁呴殰澶嶄綅淇″彿
#define SL_OCS_OPENSTAC		0xCB			//=1绂佹闂悎瀹氬瓙鎺ヨЕ鍣�1=绂佹闂悎
#define SL_PCOCS_CBOFF		0xCC			//=1PC鎺у埗鎵嬪姩鏂紑CB 1=鏂紑 2010atcpc
//canopen
#define SL_CANOPENOVER		0xCD			//=1 CANOPEN FAULT
#define SL_CANOPENHEADOK	0xCE			//=1 SL_CANOPENHEADOK
#define SL_CANOPENTX		0xCF			//=1 SL_CANOPENOVER 


//flag[13]
//LVRT鏍囧織浣�
#define SL_LV_QWORKING      0xD0       		    
#define SL_LV_MSTOP         0xD1       		    
#define SL_LV_NSTOP         0xD2
#define SL_LV_SCRON         0xD3
#define SL_LV_SCRRUNING     0xD4
#define SL_LV_SCRIZERO      0xD5
#define SL_LV_MPWMOUT		0xD6		
#define SL_LV_STATE		    0xD7		
#define SL_LV_TEST         	0xD8		
//绯荤粺閫昏緫鎺у埗 鏍囧織浣�
#define SL_SYN_S3         	0xD9			//SYN姝ラ鏍囧織浣�
#define SL_SYN_S2         	0xDA			//SYN姝ラ鏍囧織浣�
#define SL_SYN_S1     		0xDB			//SYN姝ラ鏍囧織浣�
#define SL_NORSTOP_FH      	0xDC			//NORSTOP姝ラ鏍囧織浣�
#define SL_NORSTOP_S2		0xDD			//NORSTOP姝ラ鏍囧織浣�
#define SL_NORSTOP_S1		0xDE			//NORSTOP姝ラ鏍囧織浣�
#define SL_ERRSTOP_FH		0xDF			//ERRSTOP姝ラ鏍囧織浣�

//flag[14]
#define SL_RESET            0xE0
#define SL_SIOVST           0xE1
#define SL_NPR_TLOV         0xE2
#define SL_MPR_TLOV         0xE3
#define SL_STACKEEPON		0xE4			//=1瀹氬瓙骞剁綉鐢垫祦杈冨ぇ锛屽畾瀛愭帴瑙﹀櫒绂佹鏂紑 20100510
#define	SL_TAOV				0xE5			//=1缃戜晶瓒呮俯
#define SL_TBOV			    0xE6			//=1鏈轰晶瓒呮俯
#define SL_SKTOV            0xE7            //=1杞欢鍒ゆ柇SKIIP瓒呮俯
#define SL_SERIESTOPING    	0xE8			//=1姝ｅ湪涓ラ噸鏁呴殰鍋滄満杩囩▼
#define	SL_ERRSTOPING       0xE9      		//=1姝ｅ湪涓�埇鏁呴殰鍋滄満杩囩▼
#define SL_NORSTOPING       0xEA            //=1姝ｅ湪姝ｅ父姝ｅ父鍋滄満杩囩▼
#define	SL_UDSTACOK       	0xEB      		//=1瀹氬瓙鍘嬪樊杈惧埌骞剁綉璺�
#define SL_CBON_FH       	0xEC            //=1CBON姝ラ鏍囧織浣�
#define SL_SERSTOP_FH       0xED            //=1SERSTOP姝ラ鏍囧織浣�
#define SL_HIDCOV         	0xEE			//=1涓棿鐩存祦鏂╂尝IGBT纭欢鏁呴殰20120228atbjtu_chopper	BJTULVRT201204
#define SL_SYN_FH         	0xEF   			//SYN姝ラ鏍囧織浣�




//!struct  typedef
//---2013-12-13--ZZJ澧炲姞鐢垫満鍔辩
//------------------------鐢垫満鍔辩鍙傛暟璇嗗埆MagnetCurve200909------------------------------------
struct	MC_DATA{
	float   x[6];
	float   y[6];
	float   temp[6];
	float   k;
	float   in;
}MC_DATA;
//---2013-12-13--ZZJ澧炲姞鐢垫満鍔辩

Uint32	QEP_CNT1;
Uint32	QEP_CNT2;
int16	QEPPHE_N;

float   pll_theta; 				//201011PLL
float   ptheta;
float   ntheta; 
float temp_pd;
float temp_pq;
float temp_nd;
float temp_nq; 
float   NGS_Udq_lv;

float   NGS_Udq_p;
float   NGS_Udq_n;
float   NGS_Udq_epsilon;
float   NGS_Udq_p_ex;		//20130206
float   NGS_Udq_epsilon_lv;	//20130301
float   NGS_Udq_pflt;		//20130301

float   LV_A1;				//201011LVRT
float   LV_A2;
float   LV_T1;
float   LV_T2;

float   lv_flag_flt;		//2013-12-6 LVRT鏍囧織浣嶅欢鏃惰鏁板櫒

//ModbusRS485
Uint16  length485;													//modbus
Uint16  longtx_num;													//modbus

float   RUN_mpridrf_exi;
Uint16  RUN_mpriq;
Uint16  _OUT3_TEST;
Uint16  _NQEPPCO;
Uint16  R_SCOUT;
float   Ud_lv;
float   temp_ud;

//float   NGS_Udq_p;
//float   NGS_Udq_epsilon;
float   NGS_Udq;
float   PHAI_d;
float   PHAI_q;
float   PHAI_dq;

int32   ET_SUM1;
int32   ET_SUM2;

/*涓嬮潰鐨勭敤浣淪VPWM璁＄畻*/
Uint16 SW_NPR,SW_MPR; 
float   vdc;	 
float   m=0.0;
float   ua_m=0,ub_m=0,uc_m=0;  //璋冨埗娉�
float   u_alfa_NPR=0,u_beta_NPR=0;
float   u_alfa_MPR=0,u_beta_MPR=0;


//缁欏畾鍊煎瘎瀛樺櫒
struct	GIVE{
	float   urf;					   //缃戜晶涓棿鐩存祦鐢靛帇缁欍剸锟�
	float   npriqrf;                   //缃戜晶鏃犲姛鐢垫祦缁欏畾鍊�浠呯綉渚ф棤鍔熻繍琛屾椂浣跨敤)
	float   toqrf;                      //鏈轰晶杞煩缁欏畾鍊�鏈夊姛)
	float   anglerf;                    //鏈轰晶鍔熺巼鍥犳暟瑙掑害缁欏畾鍊�鏃犲姛) 瑙掑害
	float   lvwtiqrf;                   //浣庣數鍘嬬┛瓒婃湡闂存満缁勬�鏃犲姛鐢垫祦鎸囦护20121103
	float   toqrfrun;                  //鏈轰晶杞煩缁欏畾鍊�鏈夊姛)201205LVRTatZB
	float   toqrfflt;                   //鏈轰晶杞煩缁欏畾鍊�1s澶ф护娉㈠钩鍧囧�)201205LVRTatZB
	float   npriqrf_cl;                   //缃戜晶鏃犲姛鐢垫祦缁欏畾鍊�浠呯綉渚ф棤鍔熻繍琛屾椂浣跨敤)201205LVRTatZB
	float   toqrf_lv;                      //鏈轰晶杞煩缁欏畾鍊�鏈夊姛)	20130128
}GIVE;
float OCS_Trf;                          //涓绘帶缁欒繃鏉ョ殑杞煩鎸囦护

//缁欏畾绉垎鐩稿叧瀵勫瓨鍣�
struct	RUN{									
	float   urf;						//鐢靛帇缁欏畾绉垎鍊�
	float   ustep;						//鐢靛帇缁欏畾绉垎姝ラ暱
	float   mpridrf;						//鏈夊姛鐢垫祦缁欏畾绉垎鍊�
	float   mpridstep;						//鏈夊姛鐢垫祦缁欏畾绉垎姝ラ暱
	float   npriqrf;						//鏃犲姛鐢垫祦缁櫳戭悹绉�
 	float   npriqstep;						//鏃犲姛鐢垫祦缁欏畾绉垎姝ラ暱
	float   mpriqrf;						//鏃犲姛鐢垫祦缁櫳戭悹绉�
 	float   mpriqstep;						//鏃犲姛鐢垫祦缁欏畾绉垎姝ワ拷
	float   toqrf;						//杞煩缁欏畾绉垎鍊�
	float   toqstep;					//杞煩缁欏畾绉垎姝ラ暱
	float   aglrf;						//鍔熺巼鍥犳暟瑙掔粰瀹氱Н
	float   aglstep;					//鍔熺巼鍥犳暟瑙掔粰瀹氱Н鍒嗘闀�

	float   staidrf;					//瑙ｅ垪瀹氬瓙d杞寸數娴佹寚浠�
	float   staiqrf;					//瑙ｅ垪瀹氬瓙q杞寸數娴佹寚浠�
	float   staidstep;					//瑙ｅ垪瀹氬瓙d杞寸數娴佹闀�
	float   staiqstep;					//瑙ｅ垪瀹氬瓙q杞寸數娴佹闀�

	float   mpridrf_g;						
	float   mpriqrf_g;					
 	float   mpriqrf_g_exlv;					//20130221
    
    float   radianrf;
	float   mpridrf_exi;
	float   mpridrf_var;
}RUN; 
//鍧愭爣鍙樻崲鐩稿叧瀵勫瓨鍣�
struct	TRANS_DATA{
    float a;           	//a鐩�
	float b;           	//b鐩�
	float c;           	//c鐩�
	float alfa;	       	//alfa杞�
	float beta;	       	//beta杞�
	float d;		   	//d杞�
	float q;           	//q杞�
	float sintheta;    	//姝ｅ鸡鍊�
	float costheta;	   	//浣欏鸡鍊�
	float dflt;	   		//婊ゆ尝鍚巇鍊�
	float qflt;	   		//婊ゆ尝鍚巕鍊�
	float amp;			//骞呭�
	float ampflt;		//婊ゆ尝鍚庡箙鍊�
	float dflt2;	   	//灏忔护娉㈠悗d鍊�0091027atzy涓轰簡妫�祴鐢电綉璺岃惤
//--------20121103--------
	float dpll;	   		//201011PLL
	float qpll;	   		//201011PLL
	float palfa;	    
	float pbeta;	 
	float pd;		   	
	float pq;       
	float nalfa; 	
	float nbeta;
	float nd;		   
	float nq;
    float de_pd;
    float de_pq;
    float de_nd;
    float de_nq;
    float de_fltpd;
    float de_fltpq;
    float de_fltnd;
    float de_fltnq;
	float de_psintheta;
	float de_pcostheta;	 
	float de_nsintheta;
	float de_ncostheta;	 //201011PLL 
	float dbsf;		//BJTULVRT201204
	float qbsf;	
	float dnbsf;		//BJTULVRT201204
	float qnbsf;	
    float ab;          //ab BJTULVRT201204
	float bc;           //bc

};																 
struct	TRANS_DATA TRS_NPR_I;   //缃戜晶鍙樻祦鍣ㄧ殑鐢垫祦锛堣繖閲孨PR浣滀负鍚庣紑锛屼笉鐢╣rd锛屼互鍖哄垎鐢电綉鐢垫祦杩樻槸缃戜晶鍙樻祦鍣ㄧ數娴侊級
struct	TRANS_DATA TRS_MPR_I;   //鏈轰晶鍙樻祦鍣ㄧ殑鐢垫祦
struct	TRANS_DATA TRS_MPR_U;   //鏈轰晶鍙樻祦鍣ㄧ畻鑴夊啿鐢�
struct	TRANS_DATA TRS_NPR_U;   //缃戜晶鍙樻祦鍣ㄧ畻鑴夊啿
struct	TRANS_DATA TRS_NGS_U;   //顗呭棢缂ゎ増缂拷
struct	TRANS_DATA TRS_STA_I;   //瀹氬瓙鐢垫祦
struct	TRANS_DATA TRS_STA_U;   //瀹氬瓙鐢靛帇
struct	TRANS_DATA TRS_GSTA_U;  //鐩爣瀹氬瓙鐢靛帇
struct	TRANS_DATA TRS_PSTA_U;  //鐢ㄤ簬缂栫爜鍣ㄤ綅缃娴嬬殑瀹氬瓙鐢靛帇
struct	TRANS_DATA TRS_PMPR_I;  //鐢ㄤ簬缂栫爜鍣ㄤ綅缃娴嬬殑杞瓙鐢垫祦
struct	TRANS_DATA DIP_NPR_U;  //鐢ㄤ簬鍔熺巼璁＄畻
struct	TRANS_DATA DIP_NPR_I;  //鐢ㄤ簬鍔熺巼璁＄畻
struct	TRANS_DATA DIP_STA_U;  //鐢ㄤ簬鍔熺巼璁＄畻
struct	TRANS_DATA DIP_STA_I;  //鐢ㄤ簬鍔熺巼璁＄畻
struct	TRANS_DATA DIP_MPR_I;  //鐢ㄤ簬鍔熺巼璁＄畻
struct	TRANS_DATA TRS_GAC_U;  //鐢ㄤ簬201011PLL
struct	TRANS_DATA TRS_SCR_I;   //鏈轰晶crowbar鐢垫祦BJTULVRT201204

struct I_DATA_PLL				//201011PLL
{
   	float last;
   	float out0;
   	float out1;
	float out;
}I_DATA_PLL; 

//PI鐜浉鍏冲瘎瀛樺櫒
struct PI_DATA
{
	float reference;							//缁欏畾鍊�
	float feedback;								//鍙嶉鍊�
	float errorp;								//鎷斿樊
	float error;								//璇樊
	float integrator;							//鍓嶆绉焊宄侊拷
	float out;
	float last;							//201011PLL
	float outflt;						//201011PLL 
};  
struct PI_DATA PI_NPR_Id;				//缃戜晶鍙樻祦鍣╠杞寸數娴侀棴鐜�
struct PI_DATA PI_NPR_Iq;				//缃戜晶鍙樻祦鍣╭杞寸數娴侀棴鐜�
struct PI_DATA PI_MPR_Id;				//鏈轰晶鍙橀珜楸犺酱鐢垫祦闂幆
struct PI_DATA PI_MPR_Iq;				//鏈轰晶鍙樻祦鍣╭杞寸數娴侀棴鐜�
struct PI_DATA PI_NPR_U;				//缃戜晶鍙樻祦鍣ㄧ數鍘嬬幆
struct PI_DATA PI_MPR_U;				//杞苟缃戦棴鐜�
struct PI_DATA PI_STA_Id;				//鍔辩鎺у埗d
struct PI_DATA PI_STA_Iq;				//鍔辩鎺у埗q
struct PI_DATA PI_DATA_PLL;				//201011PLL
struct PI_PARA PI_PARA_DYMI;			//鍔ㄦ�瀹藉甫瀹絇I鎺у埗BJTULVRT201204

struct PI_PARA
{
   float kp;
   float ki;
   float kd;
   float errmax;
   float errmin;
   float incrementmax;
   float outmax;
};
struct PI_PARA PI_PARA_NPRU;
struct PI_PARA PI_PARA_NPRID;
struct PI_PARA PI_PARA_MPRU;
struct PI_PARA PI_PARA_MPRID;
struct PI_PARA PI_PARA_NPRIQ;
struct PI_PARA PI_PARA_MPRIQ;
struct PI_PARA PI_PARA_DYNU;
struct PI_PARA PI_PARA_DYNID;
struct PI_PARA PI_PARA_DYNIQ;
struct PI_PARA PI_PARA_MPRI;
struct PI_PARA PI_PARA_STAI;
struct PI_PARA PI_PARA_PLL;				//201011PLL


//椁劥鑼冦剨閫奸鎶婇偖濂斿墫類拷
struct	MAIN_LOOP{
	int32 cnt1;					//涓诲惊鑼冦剨濂旈�鍣�ms
	int32 cnt2;					//涓诲惊鐜畾鏃跺瘎瀛樺櫒10ms
	int32 cnt3;					//涓诲惊鐜畾鏃跺瘎瀛樺櫒20ms
	int32 cnt4;					//涓诲惊鐜剨濂旀媷瀚拷0ms
	int32 cnt5;					//椁劥鑼冦剨濂旀媷瀚拷00ms
	int32 cnt6;					//涓诲惊鐜畾鏃跺瘎瀛橈拷000ms
	int32 pulse;				//涓诲惊鐜垎鏃惰剦鍐插瘎瀛樺櫒
    int32 cnt_AMUX;            	//鎱㈤�AD
	
	int32 cnt_poweron;			//preparation time delay
	int32 cnt_pwmout;			//PWM杈撳嚭寤舵椂
	int32 cnt_nprlamp;			//缃戜晶鑴夊啿鍙戝嚭鎸囩ず鐏棯鐑佸欢鏃惰鏁�
	int32 cnt_mprlamp;			//鏈轰晶鑴夊啿鍙戝嚭鎸囩ず鐏棯鐑佸欢鏃惰鏁�
	int32 cnt_freq;			   	//棰戠巼鍋忕Щ璁★拷
	int32 cnt_cbfreq;
	int32 cnt_estop;
	int32 cnt_rcvr;				//鏁呴殰寤舵椂鎭㈠璁℃椂
	int32 cnt_otser;			//涓ラ噸鏁呴殰寤舵椂
	int32 cnt_datasave;
	int32 cnt_datasave2;

	int32 cnt_detectdelay;		//寮�叧鎰忓鍔ㄤ綔鍒囨崲寤讹拷110818
	int32 cnt_exfault;
	int32 cnt_cbtp;
	int32 cnt_cberror;
	int32 cnt_mainkerror;
	int32 cnt_mainferror;
	int32 cnt_preerror;
	int32 cnt_stacerror;
	int32 cnt_pgovload;
	int32 cnt_qgovload;
	int32 cnt_canfault;
	int32 cnt_speedout;
	int32 cnt_uaclv1;   		//20091027atzy		
	int32 cnt_gfault1;			//顗呭槦鎷ユ瘬鏀讹拷
	int32 cnt_gfault2;			//鏈轰晶鎺ュ湴鏁呴殰
	int32 cnt_synfail;			//鍚屾骞剁綉澶辨晠闅�
	int32 cnt_nprtlov;			//缃戜晶鐢垫劅瓒呮俯
	int32 cnt_mprtlov;			//鏈轰晶鐢垫劅瓒呮俯
	int32 cnt_nskiptov;			//缃戜晶SKIIP瓒呮俯
	int32 cnt_mskiptov;			//鏈轰晶SKIIP瓒呮俯
	int32 cnt_steadyfb;			

	int32 cnt_isteady0;
    int32 cnt_mprsteady0;
	int32 cnt_senszfstdy;
	int32 cnt_qcapspdin;
	int32 cnt_qepzdisturb;
	int32 cnt_qepcntok;
	int32 cnt_qcapdisturb;

	int32 cnt_ecposcheck;		//鏈轰晶鍚姩寤惰繜妫�祴 20130801
	int32 cnt_ecpostrace;		//姣忔瑙掑害鍙樺寲锛屽欢杩熷垽鏂�20130801
//sysctl_zl_start
    int32 cnt_cbon;      		//涓绘柇闂悎瀛愮▼搴�
	int32 cnt_errstop;          //涓�埇鏁呴殰鍋滄満
	int32 cnt_serstop;          //涓ラ噸鏁呴殰鍋滄満
	int32 cnt_norstop;         	//姝ｅ父鍋滄満
	int32 cnt_epwmstop;         //涓�埇鏁呴殰灏佽剦鍐插悗寤舵椂鏂富鏂�0110829
	int32 cnt_synrun;          	//骞剁綉
	int32 cnt_sysoff;         	//姝ｅ父鍋滄満寤惰繜锛�0120321
//sysctl_zl_end 
	int32 cnt_reset;
    int32 cnt_clostacmd;
	int32 cnt_nprcmd;
	int32 cnt_mprcmd;
	int32 cnt_ein;
	int32 cnt_sysrun;
	int32 cnt_prec;	

	//canopen
	int32 canopen_rx;
	int32 canopen_tx;
	int32 cnt_cbreset;

	int32 et_relay1;     
	int32 et_relay2;

	int32 cnt_ocsein1;     
	int32 cnt_ocsein2;
	int32 cnt_ocssysrun1;     
	int32 cnt_ocssysrun2;

//LVRT
	int32 cnt_scrizero;
	int32 cnt_lv_scron;
	int32 cnt_lv_mpwmstart;
	int32 cnt_lv_mpwmstop;
	int32 cnt_mpwmrestart;
	int32 cnt_npwmrestart;
	int32 cnt_lv_state;
	int32 cnt_lv_rcv;
	int32 cnt_lv_time;
	int32 cnt_lv_test;
	int32 cnt_scrondelay;
	int32 cnt_lv_fault1;
	int32 cnt_lv_fault2;
	int32 cnt_mc_ack;   		//MagnetCurve2013-12-13	
	
	int32 cnt_resetrn;
	int32 cnt_phorde;   		//201005atcpc	
	int32 cnt_encofault;   		//201005atcpc	
//------20121103atsp-------
	int32 cnt_lv_test2;
	int32 cnt_lv_unbalance;		
	int32 cnt_lv_qworking;	
	int32 cnt_scrizero2;
	int32 cnt_lv_phicontrol;	
	int32 cnt_lv_lowpi;	
	int32 cnt_lv_mpridvar;	
	int32 cnt_lv_utlv;
	int32 cnt_idcov;
	int32 cnt_idcovdelay;
	int32 cnt_freqrecv;			//201011PLL
	int32 cnt_lv_irqdelay;		//20121202
	int32 cnt_vdscron;			//20121203
	int32 cnt_vdscroff;			//20121203

//--------20130225atsp--------
	int32 cnt_lv_scroff1;		//20121210
	int32 cnt_lv_scroff2;		//20121210
	int32 cnt_lv_scroff3;		//20130221
	int32 cnt_lv_unblcscroff1;		//20121210
	int32 cnt_lv_unblcscroff2;		//20121210

	int32 cnt_lv_nprqworking;		//20130124
	int32 cnt_lv_npriqrf;			//20130124
	int32 cnt_lv_mpridrf;			//20130130
	int32 cnt_lv_kq;				//20130124
	int32 cnt_lv_unblcscroff3;		//20130124
	int32 cnt_lv_recmstop;			//20130124
	int32 cnt_lv_dlrecmstop;		//20130130
	int32 cnt_lv_xnzkkz;			//20130202
	int32 cnt_jgvdscron;			//20130205
	int32 cnt_lv_reciq;				//20130205
	int32 cnt_lv_holdpow;			//20130205
	int32 cnt_lv_scrkeepon;			//20130221
	int32 cnt_chopper;				//2013-12-6	ZZJ鏂╂尝娴嬭瘯

}MAIN_LOOP;  

//鎱㈤�AD澶勭悊瀵勫瓨鍣�
Uint16 _OUT_AMUX1=0;  //鐢ㄤ簬鎱㈤�AD閫夐�淇″彿锛屾瘡娆¤閫夐�涓嬩竴涓狝D閫氶亾锛宊OUT_AMUX鍔�锛岀劧鍚庨�鍒癈PLD鍘诲鐞嗭紝閫夐�16閫�鑺墖
Uint16 _OUT_AMUX2;    //鐢ㄤ簬鎱㈤�AD閫夐�淇″彿锛屾瘡娆¤閫夐�涓嬩竴涓狝D閫氶亾锛宊OUT_AMUX鍔�锛岀劧鍚庨�鍒癈PLD鍘诲鐞嗭紝閫夐�16閫�鑺墖
struct  AMUX{
    float NPR_tempa;  //NPR鐨凙鐩稿崐瀵间綋娓╁害锛孲kiip浼犲洖鏉ョ殑
    float NPR_tempb;  //NPR鐨凚鐩稿崐瀵间綋娓╁害锛孲kiip浼犲洖鏉ョ殑
    float NPR_tempc;  //NPR鐨凜鐩稿崐瀵间綋娓╁害锛孲kiip浼犲洖鏉ョ殑
    float MPR_tempa;  //MPR鐨凙鐩稿崐瀵间綋娓╁害锛孲kiip浼犲洖鏉ョ殑
    float MPR_tempb;  //MPR鐨凚鐩稿崐瀵间綋娓╁害锛孲kiip浼犲洖鏉ョ殑
    float MPR_tempc;  //MPR鐨凜鐩稿崐瀵间綋娓╁害锛孲kiip浼犲洖鏉ョ殑
    float Lac_temp;   //浜ゆ祦娴嬬數鎰熸俯搴�
	float Ldudt_temp; //du/dt鐨勬俯搴�
	float skiiptempmax;    //SKIIP妯″潡鐨勬俯搴︽渶澶у�
	float NPR_skiiptemp;    //缃戜晶SKIIP妯″潡鐨勬俯搴︽渶澶у�
	float MPR_skiiptemp;    //鏈轰晶SKIIP妯″潡鐨勬俯搴︽渶澶у�
	float Lac_R;   			//浜ゆ祦鐢垫劅pt100
	float Ldudt_R; 			//du/dt鐨刾t100

}AMUX;

//AD妯″潡澶勭悊瀵勫瓨鍣�
struct	AD{
	int16  dat[18];													//AD褰撳墠杞崲缁撴灉瀛樻斁
	Uint32 cputime;
	Uint32 cputime_last;
}AD;

//AD杞崲缁撴灉瀵勫瓨鍣�
struct	ADFINAL{
	int16  ia1;				//缃戜晶A鐩哥數娴�
	int16  ib1;				//缃戜晶B鐩哥數娴�
	int16  ic1;				//缃戜晶B鐩哥數娴�
	int16  ia2;				//鐢垫満渚鐩哥數娴�
	int16  ib2;				//鐢垫満渚鐩哥數娴�
	int16  ic2;				//鐢垫満渚鐩哥數娴�
	int16  isa;              //瀹氬瓙鐢垫祦A鐩�
    int16  isc;              //瀹氬瓙鐢垫祦C鐩�
    int16  idc;              //chopper鐢垫祦
    int16  freq;            //VVVF璋冭瘯鏃剁敤鍋氱數浣嶅櫒缁欏畾棰戠巼
	int16  uab1;			//缃戜晶ab绾垮帇
	int16  ubc1;			//缃戜晶bc绾垮帇
	int16  uab2;			//鐢垫満瀹氬瓙渚b绾垮帇
	int16  ubc2;			//鐢垫満瀹氬瓙渚c绾垮帇
	int16  uab3;			//鐢电綉鐢靛帇ab锛堜富鏂悗锛夊ぇ婊ゆ尝閫氶亾
	int16  ubc3;			//鐢电綉鐢靛帇bc锛堜富鏂悗锛夊ぇ婊ゆ尝閫氶亾
    int16  udc;             //鐩存祦鐢靛帇
    int16  ubc;			    //涓绘柇鍓峛c绾垮帇
	int16  uab;			    //涓绘柇鍓峚b绾垮帇
    int16  AMUX;            //鎱㈤�AD淇″彿



}ADFINAL;
   

//缃戝帇鐭㈤噺
struct AD_DATA{
	  float  a;
	  float  b;
	  float  c;
	  float  ab;
	  float  bc;
	  float  ac;
	  float  cb;
	  float  ba;
	  float  a_temp;
	  float  b_temp;
	  float  c_temp;
	  float  ab_temp;
	  float  bc_temp;
	  float  a_dc;
	  float  b_dc;
	  float  c_dc;
	  float  ps;
};
struct AD_DATA AD_OUT_GRD_U;  //鐢电綉鐢靛帇锛堜富鏂墠锛�
struct AD_DATA AD_OUT_STA_U;  //鐢垫満瀹氬瓙渚х數鍘�澶ф护娉㈤�閬�
struct AD_DATA AD_OUT_NGS_U;  //鐢电綉鐢靛帇锛堜富鏂悗锛�
struct AD_DATA AD_OUT_NPR_I;  //缃戜晶鍙樻祦鍣ㄧ數娴�
struct AD_DATA AD_OUT_MPR_I;  //鏈轰晶鍙樻祦鍣ㄧ數娴�
struct AD_DATA AD_OUT_STA_I;  //瀹氬瓙渚х數娴�
struct AD_DATA AD_OUT_NGF_U;  //鐢电綉鐢靛帇锛堜富鏂悗锛夊ぇ婊ゆ尝閫氶亾
struct AD_DATA AD_OUT_STAD_U;  //宸�
struct AD_DATA AD_OUT_SCR_I;  //ACTIVECROWBAR鐢垫祦
struct AD_DATA AD_OUT_DC_I;  //CHOPPER鐢垫祦

float  AD_OUT_UDC; //AD璁＄畻鍚庤緭鍑虹殑鐩存祦鐢垫鈺掞級

//姹傚钩鍧囧�
struct MEAN_DATA{
       float ia1,ib1,ic1;  			//缃戜晶鐢垫祦骞冲潎鍊兼护娉�
	   float ia2,ib2,ic2;  			//鏈轰晶鐢垫祦骞冲潎鍊兼护娉�
	   float ia3,ib3,ic3;  			//瀹氬瓙渚х數娴佸钩鍧囧�婊ゆ尝
	   float uab1,ubc1;	   			//缃戜晶鐢靛帇骞冲潎鍊兼护娉�
	   float uab2,ubc2;	   			//瀹氬瓙渚х數鍘嬪钩鍧囧�婊ゆ尝
	   float uab3,ubc3;	   			//涓绘柇鍚庣數缃戠數鍘�澶ф护娉㈤�閬搈agnetCurve2013-12-13
	   float ua1,ub1,uc1;	   		//缃戜晶鐢靛帇骞冲潎鍊兼护娉�
	   float uab_d,ubc_d;	   		//缃戜晶涓庡畾瀛愪晶鐢靛帇骞冲潎鍊煎樊 澶ф护娉㈤�閬�
	   float zfia1,zfib1,zfic1; 	//缃戜晶鐢垫祦浼犳劅鍣ㄩ浂婕傛护娉�
	   float zfia3,zfib3,zfic3; 	//瀹氬瓙渚х數娴佷紶鎰熷櫒闆舵紓婊ゆ尝
	   float zfuab1,zfubc1; 		//缃戜晶鐢靛帇浼犳劅鍣ㄩ浂婕傛护娉�
	   float zfuab2,zfubc2; 		//瀹氬瓙鐢靛帇浼犳劅鍣ㄩ浂婕傛护娉�
	   float zfuab3,zfubc3; 		//缃戜晶鐢靛帇 澶ф护娉㈤�閬�闆舵紓婊わ拷
	   float nid,niq,nud,nuq;    	//瀵筃PR閲忚繘琛屾护娉�
	   float uab,ubc;	   			//涓绘柇鍓嶇綉渚х數鍘嬪钩鍧囧�婊ゆ尝
	   float zfuab,zfubc; 		    //涓绘柇鍓嶇數鍘嬩紶鎰熷櫒闆舵紓婊ゆ尝
	   float udc;
	   float iac3,iba3,icb3;				//瀹氬瓙渚х數娴佸钩鍧囧�婊ゆ尝
	   float psactive;				//瀹氬瓙渚х數娴佸钩鍧囧�婊わ拷
	   float Lac_temp,Ldudt_temp;   //鐢垫劅娓╁害婊ゆ尝
	   float ubc_t;					//20130801
	   	   
}MEAN_DATA;  

//淇濇姢妯″潡缁撴灉鍙橀噺
struct	PRO{									
	         	float	NPR_iac;								//骞剁綉鐢垫祦宄板�,鍩哄噯鐢垫祦鐨勭櫨鍒嗗�
				float	MPR_iac;								//瀹氬瓙鐢垫祦宄板�,鍩哄噯鐢垫祦鐨勭櫨鍒嗗�
				float	udc;									//涓棿鐩存祦鐢靛帇姝ｅ疄闄呭�(V)
				float	NPR_uab;								//缃戜晶 ab绾跨數鍘嬪疄闄呭�(V)
				float	NPR_ubc;								//缃戜晶 bc绾跨數鍘嬪疄闄呭�(V)
				float	STA_uab;								//瀹氬瓙渚�ab绾跨數鍘嬪疄闄呭�(V)
				float	STA_ubc;								//瀹氬瓙渚�bc绾跨數鍘嬪疄闄呭�(V)
				float	GID_uab;								//鐢电綉渚�ab绾跨數鍘嬪疄闄呭�(V) 20091026atzy
				float	GID_ubc;								//鐢电綉渚�bc绾跨數鍘嬪疄闄呭�(V) 20091026atzy
				float	rcvr;									//寤惰繜鎭㈠鏃堕棿
				float   STA_iac;                            	//瀹氬瓙浜ゆ祦鐢垫祦iac
				float   STA_icb;                            	//瀹氬瓙浜ゆ祦鐢垫祦iba
   				float   NPR_TLOV;                            	//缃戜晶鐢垫劅娓╁害
				float   MPR_TLOV;                            	//鏈轰晶鐢垫劅娓╁害
				float   speed;                               	//鐢垫満杞� r/min
				float   speedflt;                               //20090815
				float   sta_iar;	  							//瀹氬瓙渚鐩哥數娴丄 RMS
				float   sta_ibr;	  							//瀹氬瓙渚鐩哥數娴丄 RMS
				float   sta_icr;	  							//瀹氬瓙閮肩數娴丄 RMS
				float   sta_uar;	  							//瀹氬瓙渚鐩哥數鍘媀 RMS
				float   sta_ubr;	  							//瀹氬瓙渚鐩哥數鍘媀 RMS
				float   sta_ucr;	 							//瀹氬瓙閮煎棢缂瓡 RMS
				float   npr_uar;	  							//缃戜晶a鐩哥數鍘媀 RMS
				float   npr_ubr;	  							//缃戜晶b鐩哥數鍘媀 RMS
				float   npr_ucr;	  							//缃戜晶c鐩哥數鍘媀 RMS
				float   npr_iar;   								//缃戜晶,A鐩稿苟缃戠數娴佹湁鏁堝�,鍗曚綅A
				float   npr_ibr;	  							//缃戜晶,B鐩稿苟缃戠數娴佽械锟藉崟浣岮
				float   npr_icr;	  							//顗咃拷C鐩稿苟顗堢紝楗旇械锟藉崟浣岮
				float   Psactive; 								//瀹氬瓙渚ф硠顪ノ诧拷
				float   Psreactive; 							//瀹氬瓙渚ф棤鍔熷姛鐜�
				float   Ps;          							//瀹氬瓙渚ц鍦ㄥ姛鐜�
				float   Pnactive;    							//缃戜晶鏈夊姛鍔熺巼
				float   Pnreactive;  							//缃戜晶鏃犲姛鍔熺巼
				float   Pn;          							//缃戜晶瑙嗗湪鍔熺巼
				float   Pgactive;    							//骞剁綉鎬荤殑鏈夊姛鍔熺巼
				float   Pgreactive;  							//缃戜晶鎬婚湏鍔熷姛鐜�
				float   Pg;       								//鈶碱壀鑹挎皷閲夎癄尾锟�
				float	CHOP_idc;								//chopper鐢垫祦姝ｅ疄闄呭�(A)20120228	BJTULVRT201204
				float   Psactive2; 								//瀹氬瓙渚ф湁鍔熷姛鐜�
				float   Psreactive2; 							//銊楃‖鍣㈠姛鍔熺巼
				float   Pnactive2;    							//缃戜晶鏈夊姛鍔熺巼
				float   Pnreactive2;  							//缃戜晶鏃犲姛鍔熺巼
				float   Pgactive2;    							//骞剁綉鎬荤殑鏈夊姛鍔熺巼
				float   Pgreactive2;  							//缃戜晶鎬婚湏鍔熷姛鐜�

				float   Pgactive_lv;   							//LVRT鍓嶇殑鍔熺巼20121210

		   }PRO; 
 
//鏄剧ず鍡箛娣烇拷
struct	DISP{										
    			float  npr_iai;   //缃戜晶,A鐩稿苟缃戠數娴佺灛鏃跺�,鍗曚綅A
				float  npr_ibi;	  //缃戜晶,B鐩稿苟缃戠數娴佺灛鏃跺�,鍗曚綅A
				float  npr_ici;	  //缃戯拷C鐩稿苟缃戠紝榄夊僵鏁濓拷銉庣眲
				float  mpr_iai;	  //鐢垫満渚�A鐩哥數娴佺灛鏃跺�,鍗曚綅A
				float  mpr_ibi;	  //鐢垫満渚�B鐩哥數娴佹暆锟藉崟浣岮
				float  mpr_ici;   //鐢垫満渚�C鐩哥數娴佹椂鍊�鍗曚綅A
				float  npr_iar;   								//缃戜晶,A鐩稿苟缃戠數娴佹湁鏁堝�,鍗曚綅A
				float  npr_ibr;	  							//缃戜晶,B鐩稿苟缃戠數椁嶆晥鍊�鍗曚綅A
				float  npr_icr;	  							//缃戜晶,C鐩稿苟缃戠數娴佹湁鏁堝�,鍗曚綅A
				float  mpr_iar;	  //鐞ヤ晶,A鐩哥數娴佹湁鏁堝�,鍗曚綅A
				float  mpr_ibr;	  //鐢垫満渚�B鐩哥數娴佹湁鏁堝�,鍗曚綅A
				float  mpr_icr;   //鐢垫満渚�C鍡熺紝楗旇械锟姐儙绫�
    			float  npr_uab;	  //缃戜晶ab鐩哥數鍘媀 RMS
				float  npr_ubc;	  //缃戜晶bc鐩哥數鍘媀 RMS

				float  sta_uab;	  //瀹氬瓙渚b鐩哥數鍘媀 RMS
				float  sta_ubc;	  //瀹氬瓙渚c鐩哥數鍘媀 RMS
				float  sta_iac;	  //瀹氬瓙渚х嚎鐢垫祦A RMS
				float  sta_iba;	  //瀹氬瓙渚х嚎鐢垫祦A RMS

				float  grd_uab;   //涓绘柇鍓嶇綉渚b鐢靛帇V RMS
				float  grd_ubc;   //涓绘柇鍓嶇綉渚c鐢靛帇V RMS
				float  uab23;     //瀹氬瓙鍚屾骞剁綉鍓嶅畾瀛愬墠鍚巃b鐢靛帇宸�V
				float  ubc23;     //瀹氬瓙鍚屾骞剁綉鍓嶅畾瀛愬墠鍚巄c鐢靛帇宸�V
				float  Lac_temp;  //缃戜晶缁哄舰闇诧拷鎽勬皬搴�
				float  Ldudt_temp;  //鏈轰晶鐢垫劅娓╁害 鎽勬皬搴�
				float  NPR_skiptemp;  //SKIIP娓╁害 鎽勬皬搴�
				float  MPR_skiptemp;  //SKIIP娓╁害 鎽勬皬搴�
				float  urf;
				float  udc;
				float  mpridrf;
				float  npriqrf;
				float  mpriqrf;
				float  toqrf;
				float  toqfb;
				float  aglrf;
				float  freq;
				float  speed;
				float  pionu;   	//缃戝棢缂鑲ュ嚭
				float  pionid;		//缃戜晶鐢垫祦d鐜緭鍑�
				float  pioniq;		//缃戜晶鐢垫祦q鐜緭鍑�
				float  mexi;		//
				float  piomid; 		//鏈轰晶鐢垫祦d鐜緭鍑�
				float  piomiq; 		//鏈轰晶鐢垫祦q鐜緭鍑�
				float  Psactive; 	//瀹氬瓙渚ф湁鍔熷姛鐜�
				float  Psreactive; 	//瀹氬瓙渚ф棤鍔熷姛锟�
				float  Ps;          //瀹氬瓙渚ц鍦ㄥ姛鐜�
				float  Pnactive;    //缃戜晶鏈夊姛鍔熺巼
				float  Pnreactive;  //缃戜晶鏃犲姛鍔熺巼
				float  Pn;          //缃戜晶瑙嗗湪鍔熺巼
				float  Pgactive;    //骞剁綉鎬荤殑鏈夊姛鍔熺巼
				float  Pgreactive;  //缃戜晶鎬荤殑鏃犲姛鍔熺巼
				float  Pg;       	//骞剁綉鎬荤殑瑙嗗湪鍔熺巼
			}DISP;
 
//鐥樻ā鍧楀彉閲�
struct CAP_DATA	{
					float		prd;				//Cap4浜嬩欢鍛ㄦ湡
					Uint32		adsmptsctr; 		//AD閲囨牱鏃跺埢鐨凜ap4璁℃暟鍣ㄥ�(鏈AD鍦–AP4涔嬪悗杩愯)
					float 		phase;	    		//浜嬩欢褰撳墠鐩镐綅//鐢ㄤ簬鐩稿簭妫�煡
					float 		freqtmp;			//鏁棶褰曨拲寰凤拷
					float 		freq;	    		//纭鍚庣殑棰戠巼
					float	    omigasyn;			//鍚屾瑙掗鐜囷紞鐢甸鐜�
					float 		omigaslp;	    	//杞樊瑙掗鐜�
					float	    radpertb;			//璁℃暟鍣ㄨ鍗曚綅鏃堕棿鐭㈤噺浣嶇疆澧為噺 rad per timebase
					float	    nprtrstheta;		//缃戜晶绠楁硶姝ｅ彉鎹㈣搴�
					float	    npratitheta;		//缃戜晶绠楁硶鍙嶅彉鎹㈣搴�
					float	    mprtrstheta;		//鏈哄棬鎯淬剷類氭禒鍞ゅ祵锟�
					float	    mpratitheta;		//鏈轰晶绠楁硶鍙嶅彉鎹㈣搴�
					float	    stavectheta;	    //瀹氬瓙纾侀摼鐩稿涓嶢鐩歌酱绾夸綅缃�
					float	    nprtrstheta_lv;		//缃戜晶绠楁硶姝ｅ彉鎹㈣搴�201011LVRT 201011PLL
				};
struct CAP_DATA CAP4,CAP5;

struct QEPDATA{
//----------------------杞瓙浣嶇疆妫�祴鍙橀噺-----------------------------------------------------------
					Uint16		qcapprd;		//QCAP鍗曞厓鍛ㄦ湡瀵勫瓨鍣ㄥ�锛岀敤浜庢祴鍛ㄦ硶绠楄浆閫�
					float 		omigamec;		//鏈烘瑙掗�搴�
					float 		omigarote;	    //鐢垫皵瑙掍浚锟絩otor electric
					float 		omigaroteflt;	//
					float 		rotpos;			//杞瓙褰撳墠浣嶇疆rad锛堢數寮у害锛�
					Uint32   	adsmposcnt;		//閲囨牱鏃跺埢缂栫爜鍣ㄨ鏁�
					Uint32 		posilat;        //璁板綍Z淇″彿涓婂崌娌挎椂CNT璁℃暟鍊�
					Uint32 		qposlat;        //璁板綍Unit time鍐匭EPCNT鐨勮鏁板�锛岀敤浜庢祴棰戞硶绠楄浆閫�
					Uint32 		qposlat1;        //璁板綍Unit time鍐匭EPCNT鐨勮鏁板�锛岀敤浜庢祴棰戞硶绠楄浆閫�
					Uint32 		qposlat2;        //璁板綍Unit time鍐匭EPCNT鐨勮鏁板�锛岀敤浜庢祴棰戞硶绠楄浆閫�
					float 		rotposdisp;		//DA鏄剧ず
					float 		rotradpret0;	//鐢ㄤ簬QEP Z淇″彿鎶楀共鎵�
//----------------------缂栫爜鍣ㄤ綅缃娴嬪彉閲�-------------------------------------------------------
					float 		encodpos;		//缂栫爜鍣ㄤ綅缃畆ad锛堢數寮у害锛�
					float 		u_stapos;		//2S鍙傝�绯讳笅瀹氬瓙鐢靛帇鐭㈤噺鐨勪綅缃畆ad锛堢數寮у害锛�
					float 		i_rotpos;		//2S鍙傝�绯讳笅杞瓙鐢垫祦鐭㈤噺鐨勪綅缃畆ad锛堢數寮у害锛�
			  }QEPDATA; 

//SCI妯″潡鍙橀噺
struct	SCI{
					Uint16 txb[2100];				//SCIB鍙戦�鏁版嵁//modbus
					Uint16 rxb[SCI485NUM_RX];		//SCIB鎺ユ敹鏁版嵁//modbus
					int32 cnt_sciover;				//SCI鍙戦�/鎺ユ敹瓒呮椂瀹氭椂鍣�
					int32 cnt_scispace;				//SCI鎺ユ敹鍒板彂閫佺殑闂撮殧瀹氭椂鍣�
		   }SCI;

//SCICANOPEN妯″潡鍙橀噺
struct	SCI_CANOPEN{
					Uint16 txb[SCICANOPENTXNUM];			//SCIB鍙戦�鏁版嵁
					Uint16 rxb[SCICANOPENRXNUM];			//SCIB鎺ユ敹鏁版嵁
					Uint16 heartbeat;
					int32  cnt_heartbeat;
					int32  cnt_sciover;
					Uint16 rx_controlword;
					Uint16 rx_torque;
					Uint16 rx_angle;
					Uint16 tx_torque;
					Uint16 tx_speed;
					Uint16 tx_state1;
					Uint16 tx_state2;	
					Uint16 tx_watertempin;
					Uint16 tx_watertempout;
					Uint16 tx_skiiptempmax;
					Uint16 tx_demand;
		   }SCI_canopen;

//SPI妯″潡鍙橀噺
struct	SPI{
					Uint16 da7614_txb[SPINUM];		//SPI,DA鍙戦�鏁版嵁
					Uint16 da7614point;				//
		   }SPI;

//EEPROM妯″潡鍙橀噺
struct	EEPROM{
				Uint16 data[11];					//璇诲嚭鎴栧啓鍏ョ殑鏁版嵁
				Uint16 point;						//EEPROM褰撳墠浣滃彉閲忓簭鍙�
				Uint16 mcode;						//闇�淇敼鐨勫姛鑳界爜鍚嶇О
			  }EEPROM;

//RTIMER妯″潡鍙橀噺
struct	RTIMER{
				Uint16 time[6];				//褰撳墠鏃堕棿[5~0]-->骞�鏈�鏃�鏃�鍒�绉掞紙鍧囦负8浣嶆暟鎹級
			  }RTIMER;

//纾侀摼瑙傛祴BJTULVRT201204
struct PHI_DATA
{  
   float PHId;							//d杞寸閾�
   float PHIq;							//q杞寸閾�
   float PHIdflt;						//d杞寸數娴佽ˉ鍋挎寚浠�
   float PHIqflt;						//q杞寸數娴佽ˉ鍋挎寚浠�
   float PHIdflt2;						//d杞寸數娴佽ˉ鍋挎寚浠�
   float PHIqflt2;						//q杞寸數娴佽ˉ鍋挎寚浠�
   float PHIMd;							//d杞寸閾�鐢ㄤ簬ims鍔ㄦ�琛ュ伩
   float PHIMq;							//q杞寸閾�鐢ㄤ簬ims鍔ㄦ�琛ュ伩
   float PHIMdflt;						//d杞寸閾�鐢ㄤ簬ims鍔ㄦ�琛ュ伩
   float PHIMqflt;						//q杞寸閾�鐢ㄤ簬ims鍔ㄦ�琛ュ伩
   float Ird;							//d杞磋浆瀛愮數娴�
   float Irq;							//q杞磋浆瀛愮數娴�
   float Isd;							//d杞村畾瀛愮數娴�
   float Isq;							//q杞村畾瀛愮數娴�
   float Isdflt;							//d杞村畾瀛愮數娴�
   float Isqflt;							//q杞村畾瀛愮數娴�
   float ISD;							//d杞村畾瀛愮數娴�
   float ISQ;							//q杞村畾瀛愮數娴�
   float Id;							//d杞寸數娴佽ˉ鍋挎寚浠�
   float Iq;							//q杞寸數娴佽ˉ鍋挎寚浠�
   float Id_max;						//d杞寸數娴佽ˉ鍋挎寚浠ら檺骞�
   float Iq_max;						//q杞寸數娴佽ˉ鍋挎寚浠ら檺骞�
   float Id_min;						//d杞寸數娴佽ˉ鍋挎寚浠ら檺骞�
   float Iq_min;						//q杞寸數娴佽ˉ鍋挎寚浠ら檺骞�
   float theta;							//纾侀摼鍙樻崲瑙掑害
   float k;								//鍔辩Lm鏍℃绯绘暟
   float PHId0;							//d杞寸閾剧ǔ鎬佸� 201203
   float PHIq0;							//q杞寸閾剧ǔ鎬佸�
   float IMD;							//杞瓙鐢垫祦
   float IMQ;							//杞瓙鐢垫祦
   float Imd;							//d杞磋浆瀛愮數娴�
   float Imq;							//q杞磋浆瀛愮數娴�
   float Imdflt;							//d杞磋浆瀛愮數娴�
   float Imqflt;							//q杞磋浆瀛愮數娴�
};
struct PHI_DATA PHI_DATA_M; 

//201110bs
struct BS_DATA
{
	float in;					//in(k)
	float inp;					//in(k-1)
	float infp;					//in(k-2)
	float out;					//out(k)
	float outp;					//out(k-1)
	float outfp;				//out(k-2)
};  
struct BS_DATA BS_MPR_Id;				//杞瓙渚х數娴乨杞�
struct BS_DATA BS_MPR_Iq;				//杞瓙渚х數娴乹杞�
struct BS_DATA BS_STA_Id;				//瀹氬瓙渚х數娴乨杞�
struct BS_DATA BS_STA_Iq;				//瀹氬瓙渚х數娴乹杞�
struct BS_DATA BS_NPR_Ud;				//缃戜晶鍙樻祦鍣╠杞�
struct BS_DATA BS_NPR_Uq;				//缃戜晶鍙樻祦鍣╠杞�
struct BS_DATA BS_NPR_Udn;				//缃戜晶鍙樻祦鍣╠杞�
struct BS_DATA BS_NPR_Uqn;				//缃戜晶鍙樻祦鍣╠杞�

struct BS_PARA
{
   float f0;
   float fb;
   float outmax;
};
struct BS_PARA BS_PARA_MPRI;
struct BS_PARA BS_PARA_STAI;
struct BS_PARA BS_PARA_NPRU;




//-----------------------------鍐呴儴鍙橀噺----------------------------------------------------------
Uint16  _NULL_VAL=0;
Uint16  _MSG_SCOUT1;												//SCOUT淇℃伅绾у埆(鍓嶆)
Uint16  _MSG_SCOUT2;												//SCOUT淇℃伅绾у埆(鏈)
Uint16  _SY_RTRN;
Uint32   POSCNT_TEST;
float   DM_imrd;   						//杞瓙鍔辩鐢垫祦
float   DM_imrq;   						//杞瓙鍔辩鐢垫祦
float   DM_Lr;							//褰撳墠閲嶈瘯娆℃暟
float   Te_feedback;                    //瀹為檯杞煩鍊煎弽棣�
float   Pnactive;    					//缃戜晶鏈夊姛鍔熺巼
float   Pnreactive;    					//缃戜晶鏃犲姛鍔熺巼
float   Pcreactive;    					//缃戜晶鐢靛鏃犲姛鍔熺巼201205LVRTatZB
//----------------------------鍙傛暟鍙橀噺------------------------------------------------------------
Uint16 _MC_TYPE;						//鏈哄瀷鍙傛暟
Uint16 _MC_REV;							//杞欢鐗堟湰
Uint16 _MC_DATE;						//鍑哄巶鏃ユ湡
Uint16 _MC_ID;							//浜у搧缂栧彿
Uint16 _SCIB_ADDR;						//485鑺傜偣鍦板潃
Uint16 _PROSTDBY1;						//
Uint16 _PROSTDBY2;						//

Uint16 _SW_FR;							//寮�叧棰戠巼(kHz)
Uint16 _DEADTIME;						//鑴夊啿鐨勬渶灏忓閫氭椂闂�us)
Uint16 _COMPTIME;						//鑴夊啿鐨勬渶灏忓閫氭椂闂�ms)
Uint16 _MINONTIME;						//鑴夊啿鐨勬渶灏忓閫氭椂闂�us)

Uint16 _RU_UDCT;						//鐢靛帇鎸囦护绉垎鏃堕棿(ms)
Uint16 _RU_IDT;							//鐢垫祦鎸囦护绉垎鏃堕棿(ms)
Uint16 _RU_IQT;							//鐢垫祦鎸囦护绉垎鏃堕棿(ms)
Uint16 _RU_TOQT;						//杞煩鎸囦护绉垎鍙�ms)
Uint16 _RU_AGLT;                        //鍔熺巼鍥犳暟瑙掓寚浠ょН鍒嗘椂闂�ms)
Uint16 _URF;							//鐩存祦鐢靛帇缁欏畾鍊�
Uint16 _MIDRF;							//d杞寸數娴佺粰瀹氬�
Uint16 _NIQRF;							//q杞寸數娴佺粰瀹氬�
Uint16 _MIQRF;							//q杞寸數娴佺粰瀹氬�
Uint16 _TOQRF;							//杞煩鎸囦护
Uint16 _AGLRF;							//鏈轰晶鍔熺巼鍥犳暟瑙�
Uint16 _EIDCO;							//鎵嬪姩 鏈轰晶鍔辩鐢垫祦璋冩暣绯绘暟
Uint16 _ENCODPOS;						//鎵嬪姩 缂栫爜鍣ㄥ垵濮嬩綅缃搴�

Uint16 _STDBY1;							//澶囩敤1
Uint16 _STDBY2;							//澶囩敤2
Uint16 _STDBY3;							//澶囩敤3
Uint16 _STDBY4;							//澶囩敤4
Uint16 _STDBY5;							//澶囩敤5
Uint16 _STDBY6;							//澶囩敤6
Uint16 _STDBY7;							//澶囩敤7
//Uint16 _STDBY8;							//澶囩敤8
Uint16 _MC_OK;							//澶囩敤8	 MagnetCurve2013-12-13
Uint16 _STDBY9;							//澶囩敤9
Uint16 _STDBY10;						//澶囩敤10
Uint16 _STDBY11;						//澶囩敤11
Uint16 _STDBY12;						//澶囩敤12
Uint16 _STDBY13;						//澶囩敤13
Uint16 _STDBY14;						//澶囩敤14
float _eidco;
float _encodpos;
float _sc_freq1;
float _sc_freq2;

//----'鏁板瓧閲忓彉閲�PC------
Uint16 _COMMAND1;
Uint16 _COMMAND2;
Uint16 _PCEROTRIG;					    //20100308
Uint16 _DISPLAY;
Uint16 _STATE1;
Uint16 _STATE2;
Uint16 _INPUT;
Uint16 _OUTPUT;
Uint16 _LVRT;

float _stdby01;							//澶囩敤缁忚繃灏忔暟鐐瑰鐞嗗悗鍊�
float _stdby02;							//澶囩敤缁忚繃灏忔暟鐐瑰鐞嗗悗鍊�
float _stdby03;							//璧ｇ粡杩囧皬鏁扮偣澶勭牀绗撅拷
float _stdby04;							//澶囩敤顒差惞鈭堫悶鎰︻湰鐮楃锟�
float _stdby05;							//澶囩敤缁忚繃灏忔暟澶勭悊鍚庡�
float _stdby06;							//澶囩敤缁忚繃灏忔暟鐐瑰鍊�
float _stdby07;							//澶囩敤缁忚繃灏忔暟鐐瑰鐞嗗悗鍊�
float _stdby08;							//澶囩敤缁忚繃灏忔暟鐐瑰鐞嗗悗鍊�
//------------------------杩愯妯″紡鍙橀噺-------------------------------------------------------------
Uint16 _ENSCR;							//

//-----------------------PI鐜弬鏁板彉閲�-------------------------------------------------------------
Uint16	_NPR_U_Kp;		  		//缃戜晶鍙樻祦鍣ㄧ數鍘嬮棴鐜瘮渚嬬郴鏁�
Uint16	_NPR_U_Ki;		   		//缃戜晶娣為珜闉吉璐℃爤鍧婎悹绐掑嚦锟�
Uint16	_NPR_U_Kd;		   		//缃戜晶婢夊櫒鐢靛帇闂偤鈷庣獟鍑筹拷
Uint16	_NPR_U_outmax;			//缃戜晶鍙樻祦鍣ㄧ吉璐℃爤鑲ユ稇楸胯柟锟�
Uint16	_NPR_U_errmax;		 	//缃戜晶鍙樻祦鍣ㄧ數鍘嬮棴鐜宸檺骞�
Uint16	_NPR_U_errmin;		   	//缃戜晶鍙樻祦闉吉璐℃爤鑲鸿煕閾戝厔锟�
Uint16	_NPR_U_incrementmax;	//缃戜晶鍙樻祦鍣ㄧ數鍘嬮棴鐜閲忛檺骞�

Uint16	_NPR_ID_Kp;				//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜瘮渚嬬郴鏁�
Uint16	_NPR_ID_Ki;	   			//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜Н鍒嗙郴鏁�
Uint16	_NPR_ID_Kd;	   			//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜井鍒嗙郴鏁�
Uint16	_NPR_ID_outmax;			//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜緭楸胯柟锟�
Uint16	_NPR_ID_errmax;	 		//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜宸檺骞�
Uint16	_NPR_ID_errmin;	  		//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜宸挌鈮堬拷
Uint16	_NPR_ID_incrementmax; 	//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜毥鑲柟锟�

Uint16	_NPR_IQ_Kp;				//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜瘮渚嬬郴鏁�
Uint16	_NPR_IQ_Ki;	   			//缃戜晶鍙橀珜闉紝闉呮爤鍧婎悹绐掑嚦锟�
Uint16	_NPR_IQ_Kd;	   			//缃戝暰娣為珜闉紝闉呮爤鑲衡拵绐掑嚦锟�
Uint16	_NPR_IQ_outmax;			//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜緭鍑洪檺骞�
Uint16	_NPR_IQ_errmax;	 		//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜宸檺骞�
Uint16	_NPR_IQ_errmin;	  		//缃戝暰娣為珜闉紝闉呯幆璇樊鏈�皬鍊�
Uint16	_NPR_IQ_incrementmax; 	//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜閲忛檺骞�

Uint16	_MPR_U_Kp;	   			//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜瘮渚嬬郴鏁�
Uint16	_MPR_U_Ki;	  			//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜Н鍒嗙郴鏁�
Uint16	_MPR_U_Kd;	  			//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜井鍒嗙郴鏁�
Uint16	_MPR_U_outmax;	 		//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜緭鍑洪檺骞�
Uint16	_MPR_U_errmax;	  		//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜宸檺锟�
Uint16	_MPR_U_errmin;		 	//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜宸渶灏忓�
Uint16	_MPR_U_incrementmax; 	//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜閲忛檺骞�

Uint16 _MPR_ID_Kp;				//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜瘮渚嬬郴鏁�
Uint16 _MPR_ID_Ki;				//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜Н鍒嗙郴鏁�
Uint16 _MPR_ID_Kd;				//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜井鍒嗙郴鏁�
Uint16 _MPR_ID_outmax;			//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜緭鍑洪檺骞�
Uint16 _MPR_ID_errmax;			//鏈轰晶娣為珜闉紝闉呮爤鑲鸿煕閽曡柟锟�
Uint16 _MPR_ID_errmin;			//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜宸渶灏忓�
Uint16 _MPR_ID_incrementmax;		//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜閲忛檺骞�

Uint16 _MPR_IQ_Kp;				//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜瘮渚嬬郴鏁�
Uint16 _MPR_IQ_Ki;				//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜Н鍒嗙郴鏁�
Uint16 _MPR_IQ_Kd;				//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜井鍒嗙郴鏁�
Uint16 _MPR_IQ_outmax;			//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜緭鍑洪檺骞�
Uint16 _MPR_IQ_errmax;			//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜宸檺骞�
Uint16 _MPR_IQ_errmin;			//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜宸渶灏忓�
Uint16 _MPR_IQ_incrementmax;	//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜閲忛檺骞�


Uint16	_DYN_U_Kp;	   			//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜瘮渚嬬郴鏁�
Uint16	_DYN_U_Ki;	  			//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜Н鍒嗙郴鏁�
Uint16	_DYN_U_Kd;	  			//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜井鍒嗙郴鏁�
Uint16	_DYN_U_outmax;	 		//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜緭鍑洪檺骞�
Uint16	_DYN_U_errmax;	  		//鏈轰晶鍙樻祦鍣ㄧ數璐＄幆璇樊闄愬箙
Uint16	_DYN_U_errmin;		 	//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜宸渶灏忓�
Uint16	_DYN_U_incrementmax; 	//鏈轰晶鍙樻祦鍣ㄧ數璐℃爤鍚╅毥鑲柟锟�


Uint16 _SC_RTRN;													//鏁呴殰鏈�ぇ閲嶈瘯娆℃暟
Uint16 _SC_RTRT;													//涓ゆ鏁呴殰閲嶈瘯闂撮殧鏃堕棿(ms)

Uint16 _SC_IACOV1;													//鍩哄噯鐢垫祦鐨勭櫨鍒嗗�)
Uint16 _SC_UDCOV;													//涓棿鐩存祦鐢靛帇杩囧帇鍊�V)
Uint16 _SC_UDCOVH;													//涓棿鐩存祦鐢靛帇杩囧帇鍊硷紙缃戝帇璺岃惤锛�V)
Uint16 _SC_IDCOV;													//鏀逛负dc-chopper鐢垫祦淇濇姢BJTULVRT201204
//Uint16 _SC_UDCLV;													//涓棿鐩存祦鐢靛帇娆犲帇鍊�V)
Uint16 _SC_VDCON;													//涓婄數鐢靛帇
Uint16 _SC_UACOV1;													//缃戝帇浜ゆ祦鐢靛帇杩囧帇鍔ㄤ綔鍊�V)
Uint16 _SC_UACLV1;													//浜ゆ祦鐢靛帇缂虹浉鍔ㄤ綔鍊�V)
Uint16 _SC_IACOV2;													//鍩哄噯鐢垫祦鐨勭櫨鍒嗗�)
Uint16 _SC_PGOV;													//
Uint16 _SC_QGOV;													//
Uint16 _SC_IACOVST;                                                 //瀹氬瓙鐢垫祦杩囨祦淇濇姢

Uint16 _SC_Rs;														//瀹氬瓙鐢甸樆(mohm)
Uint16 _SC_Lls;														//瀹氬瓙婕忔姉(mH)
Uint16 _SC_Rr;														//杞瓙鐢甸樆(mohm)
Uint16 _SC_Llr;														//杞瓙婕忔姉(mH)
Uint16 _SC_Lm;														//鍔辩鐢碉拷mH)
Uint16 _SC_POLES;													//鏋佸鏁�
Uint16 _SC_Usn;														//瀹氬瓙棰濆畾鐢靛帇(V)
Uint16 _SC_Uro;                                                		//杞瓙寮�矾鐢靛帇(V)
Uint16 _SC_PLSPRVL;													//缂栫爜鍣ㄦ瘡鍦堝厜鏍呮暟閲�
Uint16 _SC_MSTDBY;                                               	//鐢垫満鍙傛暟澶囩敤
Uint16 _SC_EXISTY1;                                               	//鐢垫満鍔辩璋冭妭澶囩敤1
Uint16 _SC_EXISTY2;                                               	//鐢垫満鍔辩璋冭妭澶囩敤2
Uint16 _SC_EXISTY3;                                               	//鐢垫満鍔辩璋冭妭澶囩敤3
Uint16 _SC_EXISTY4;                                               	//鐢垫満鍔辩璋冭妭澶囩敤4
Uint16 _SC_EXISTY5;                                               	//鐢垫満鍔辩璋冭妭澶囩敤5

Uint16 _BA_ERR4;													//绗洓娆℃晠闅滀俊鎭�
Uint16 _BA_ERR3;													//绗笁娆℃晠闅滀俊鎭�
Uint16 _BA_ERR2;													//绗簩娆℃晠闅滀俊鎭�
Uint16 _BA_ERR1;													//绗竴娆℃晠闅滀俊鎭�
Uint16 _BA_ERR5;													//绀烘尝鍣ㄦ晠闅滀俊鎭�
//--------------------------------鎶ヨ淇℃伅鍙橈拷----------------------------------------------------
Uint16 _BA_EMIDRF;													//鏈�柊鏁呴殰鏃跺埢 d杞寸數娴佹寚浠�A)
Uint16 _BA_ENIQRF;													//鏈�柊鏁呴殰鏃跺埢 q杞寸數娴佹寚浠�A)
Uint16 _BA_EMIQRF;													//鏈�箍闅滄椂鍒�q杞寸數娴佹寚浠�A)
Uint16 _BA_ETOQRF;													//鏈�柊鏁呴殰鏃跺埢 杞煩鎸囦护(NM)
Uint16 _BA_EURF;													//鏈�柊鏁呴殰鏃跺埢 涓棿鐩存祦鐢靛帇缁欙拷V)
Uint16 _BA_EUDC;													//鏈�柊鏁呴殰鏃跺埢 涓棿鐩存祦鐢靛帇(V)
Uint16 _BA_EAGLRF;													//鏈�柊鏁呴殰鏃跺埢 鏃犲姛瑙掑害鎸囦护()
Uint16 _BA_EIA1;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶A鐩哥數娴佹湁鏁堝�(A)
Uint16 _BA_EIB1;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶B鐩哥數娴佹湁鏁堝�(A)
Uint16 _BA_EIC1;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶C鐩哥數娴佹湁鏁堝�(A)
Uint16 _BA_EIA2;													//鏈�柊鏁呴殰鏃跺埢 缂侇寔閮冪浉鐢垫祦鏈夋晥鍊�A)
Uint16 _BA_EIB2;													//鏈�柊鏁呴殰鏃跺埢 鐢垫満渚鐩哥數娴佹湁鏁堝�(A)
Uint16 _BA_EIC2;													//鏈�柊鏁呴殰鏃跺埢 鐢垫満渚鐩哥數娴佹湁鏁堝�(A)
Uint16 _BA_EUAB1;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶A鐩哥數鍘嬫湁鏁堝�(V)
Uint16 _BA_EUBC1;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶B鐩哥數鍘嬫湁鏁堝�(V)
Uint16 _BA_EUAB2;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶鐩哥數鍘嬫湁鏁堝�(V)
Uint16 _BA_EUBC2;													//鏈�柊鏁呴殰鏃跺埢 鐢垫満渚鐩哥數娴佹湁鏁堝�(V)
Uint16 _BA_EUAB0;													//鏈�柊鏁呴殰鏃跺埢 涓绘柇鍓岮B绾跨數鍘嬫湁鏁堝�(V)
Uint16 _BA_EUBC0;													//鏈�柊鏁呴殰鏃跺埢 涓婚敤鐧嘋绾跨數鍘嬫湁鏁堝�(V)
Uint16 _BA_EFREQ;													//鏈�柊鏁呴殰鏃跺埢 鐢电綉棰戠巼(hz)
Uint16 _BA_ESPEED;													//鏈�柊鏁呴殰鏃跺埢 鐢垫満杞�(rpm)
Uint16 _BA_ENPRUD;              			//d杞翠富鏂悗缃戝帇鍙嶉20091026atzy
Uint16 _BA_ENPRUQ;          				//q杞翠富鏂悗缃戝帇鍙嶉20091026atzy
Uint16 _BA_ENPRUD2;          				//d杞翠富鏂悗缃戝帇鍙嶉 婊ゆ尝鍚�0091026atzy
Uint16 _BA_ENPRUQ2;          				//q杞翠富鏂悗缃戝帇鍙嶉 婊ゆ尝鍚�0091026atzy
Uint16 _BA_ENUDOUT;          				//顗呴兛宀吉鏁呮稇锟�091026atzy
Uint16 _BA_ENUQOUT;          				//缃戜晶q杞寸數鍘嬭緭鍑�0091026atzy
Uint16 _BA_ETA1;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶鍙樻祦鍣ˋ妗ヨ噦娓╁害
Uint16 _BA_ETB1;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶鍙樻祦鍣˙妗ヨ噦娓╁害
Uint16 _BA_ETC1;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶鍙樻祦鍣–妗ヨ噦娓╁害
Uint16 _BA_ETA2;													//鏈�柊鏁呴殰鏃跺埢 鐢垫満渚у彉娴佸櫒A鐤熺暁闇诧拷
Uint16 _BA_ETB2;													//鏈�柊鏁呴殰鏃跺埢 鐢垫満渚ф窞楂岄熬妗ヨ噦娓╋拷
Uint16 _BA_ETC2;													//鏈�箍鏀堕矞绗拷鐢垫満渚у彉娴佸櫒C妗ヨ噦娓╁害
Uint16 _BA_EPIONU;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶鐢靛帇鐜緭鍑�
Uint16 _BA_EPIONID;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶d杞寸數娴佺幆杈撳嚭
Uint16 _BA_EPIONIQ;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶q杞寸數娴佺幆杈撳嚭
Uint16 _BA_EMEXI;													//鏈�柊鏁呴殰鏃跺埢 鏈轰晶鍔辩鐞嗚璁＄畻鍊兼樉绀�
Uint16 _BA_EPIOMID;													//鏈�柊鏁呴殰鏃跺埢 鏈轰晶d杞寸數娴佺幆杈擄拷
Uint16 _BA_EPIOMIQ;													//鏈�柊鏁呴殰鏃跺埢 鏈轰晶q杞寸數娴佺幆杈撳嚭
Uint16 _BA_ETLAC;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶鐢垫劅娓╁害
Uint16 _BA_ETLDUDT;													//鏈�柊鏁呴殰鏃跺埢 鏈轰晶鐢垫劅娓╁害
Uint16 _BA_ETSKIIP;													//鏈�柊鏁呴殰鏃跺埢 SKIIP娓╋拷
Uint16 _BA_ESTAIAC;	
Uint16 _BA_ESTAIBA;	
Uint16 _BA_ETOQFB;	
Uint16 _BA_EPSTA;	
Uint16 _BA_EPNPR;	
Uint16 _BA_EPGRID;	

Uint16 _BA_TIME4_0;													//鏈�柊鏁呴殰鏃堕棿(绉�
Uint16 _BA_TIME4_1;													//鏈�柊鏁呴殰鏃堕棿(锟�
Uint16 _BA_TIME4_2;													//鏈�柊鏁呴殰鏃堕棿(鏃�
Uint16 _BA_TIME4_3;													//鏈�柊鏁呴殰鏃堕棿(鏃�
Uint16 _BA_TIME4_4;													//鏈�柊鏁呴矞濂旓拷鏈�
Uint16 _BA_TIME4_5;													//鏈�柊鏁呴殰鏃堕棿(骞�

Uint16 _BA_TIME3_0;													//绗笁娆℃晠闅滄椂闂�绉�
Uint16 _BA_TIME3_1;													//绗笁娆℃晠闅滄椂闂�鍒�
Uint16 _BA_TIME3_2;													//绗笁娆℃晠闅滄椂闂�鏃�
Uint16 _BA_TIME3_3;													//绗笁娆℃晠闅滄椂闂�鏃�
Uint16 _BA_TIME3_4;													//绗笁娆℃晠闅滄椂闂�鏈�
Uint16 _BA_TIME3_5;													//绗笁娆℃晠椴滃锟藉勾)

Uint16 _BA_TIME2_0;													//绗簩闂殰鏃堕棿(绉�
Uint16 _BA_TIME2_1;													//绗簩娆℃晠闅滄椂闂�鍒�
Uint16 _BA_TIME2_2;													//绗簩娆℃晠闅滃?鏃�
Uint16 _BA_TIME2_3;													//绗簩娆℃晠闅滄椂闂�鏃�
Uint16 _BA_TIME2_4;													//绗簩娆℃晠闅滄椂闂�鏈�
Uint16 _BA_TIME2_5;													//绗簩娆℃晠闅滄椂?骞�

Uint16 _BA_TIME1_0;													//绗竴娆℃晠闅滄椂闂�绉�
Uint16 _BA_TIME1_1;													//绗竴娆℃晠闅滄椂闂�鍒�
Uint16 _BA_TIME1_2;													//绗竴娆℃晠闅滄椂闂�鏃�
Uint16 _BA_TIME1_3;													//绗竴娆℃晠闅滄椂闂�鏃�
Uint16 _BA_TIME1_4;													//绗竴娆℃晠闅滄椂闂�鏈�
Uint16 _BA_TIME1_5;													//绗竴娆℃晠闅滄椂闂�骞�

Uint16 _BA_TIME5_0;													//绀烘尝鍣ㄦ晠闅滄椂闂�绉�
Uint16 _BA_TIME5_1;													//绀烘尝鍣ㄦ晠闅滄椂闂�鍒�
Uint16 _BA_TIME5_2;													//绀烘尝鍣ㄦ晠闅滄椂闂�鏃�
Uint16 _BA_TIME5_3;													//绀烘尝鍣ㄦ晠闅滄椂闂�鏃�
Uint16 _BA_TIME5_4;													//绀烘尝鍣ㄦ晠闅滄椂闂�鏈�
Uint16 _BA_TIME5_5;													//绀烘尝鍣ㄦ晠闅滄椂闂�骞�

//-------------------------------------杩愯鐩戞帶鍙橀噺-----------------------------------------------
Uint16 _BA_MIDRF;													//d杞寸數娴佹寚浠�A)
Uint16 _BA_NIQRF;													//q杞寸數娴佹寚浠�A)
Uint16 _BA_MIQRF;													//q杞寸數娴佹寚浠�A)
Uint16 _BA_TOQRF;													//杞煩鎸囦护(NM)
Uint16 _BA_AGLRF;													//鏃犲姛瑙掑害鎸囦护(NM)
Uint16 _BA_TOQFB;													//杞煩鍙嶉(NM)
Uint16 _BA_URF;														//涓棿鐩存祦鐢靛帇缁欏畾(V)
Uint16 _BA_UDC;														//涓棿鐩存祦鐢靛帇(V)
Uint16 _BA_IA1;														//缃戦儍鐩哥數娴佹湁鏁堝�(A)
Uint16 _BA_IB1;														//缃戜晶B鐩哥數娴佹湁械?A)
Uint16 _BA_IC1;														//缃戜晶C鐩哥數娴佹湁鏁堝�(A)
Uint16 _BA_IA2;														//鐢垫満渚鐩哥數娴佹湁鏁堝�(A)
Uint16 _BA_IB2;														//鐢垫満渚鐩哥數楗旇械锟紸)
Uint16 _BA_IC2;														//鐢垫満渚鐩哥數娴佹湁鏁堝�(A)
Uint16 _BA_UAB1;													//缃戜晶AB绾跨數鍘嬫湁鏁堝�(V)
Uint16 _BA_UBC1;													//缃戜晶BC绾跨數鍘嬭械锟絍)
Uint16 _BA_UAB2;													//鐢垫満渚B绾跨數鍘嬫湁鏁堝�(V)
Uint16 _BA_UBC2;													//鐢垫満渚C绾跨數娴佹湁鏁堝�(V)
Uint16 _BA_UAB0;												    	//涓绘柇鍓岮B绾跨數鍘嬫湁鏁堝�(V)
Uint16 _BA_UBC0;												    	//涓绘柇鍓岯C绾跨數娴佹湁鏁堝�(V)
Uint16 _BA_FREQ;													//鐢电綉棰戯拷hz)
Uint16 _BA_SPEED;													//鐢垫満杞�(rpm)
Uint16 _BA_TA1;														//缃戜晶鍙樻祦鍣ˋ妗ョ暁闇�
Uint16 _BA_TB1;														//缃戜晶鍙樻祦榘炬ˉ鑷傛俯搴�
Uint16 _BA_TC1;														//缃戜晶鍙樻祦鍣–妗ヨ噦娓╁害
Uint16 _BA_TA2;														//鐢垫満渚у彉娴佸櫒A妗ヨ噦娓╁害
Uint16 _BA_TB2;														//鐢垫満渚у彉娴佸櫒B妗ヨ噦娓╁害
Uint16 _BA_TC2;														//鐢垫満渚у彉娴佸櫒C妗ヨ噦娓╁害
Uint16 _BA_PIONU;													//缃戜晶鐢靛帇鐜緭鍑�
Uint16 _BA_PIONID;													//缃戜晶d杞寸數娴佺幆杈撳嚭
Uint16 _BA_PIONIQ;													//缃戜晶q杞寸數娴佺幆杈撳嚭
Uint16 _BA_MEXI;													//
Uint16 _BA_PIOMID;													//鏈轰晶d杞寸數娴佺幆杈撳嚭
Uint16 _BA_PIOMIQ;													//鏈轰晶q杞寸數娴佺幆杈撳嚭
Uint16 _BA_GRDUD;													//浼犳劅鍣ㄦ祴閲忕綉鍘媎
Uint16 _BA_GRDUQ;													//浼犳劅鍣ㄦ祴閲忕綉鍘媞

//Uint16 _BA_STAUD;													//瀹氬瓙鐢靛帇d MagnetCurve2013-12-13
Uint16 _BA_MC_IN;													//鍔辩鏍℃杈撳叆 MagnetCurve2013-12-13
Uint16 _BA_MC_K;													//鍔辩鏍℃杈撳嚭 MagnetCurve2013-12-13
//Uint16 _BA_STAUQ;													//瀹氬瓙鐢靛帇q MagnetCurve2013-12-13

Uint16 _BA_NPRID;													//浼犳劅鍣ㄦ祴閲忕綉鍘媎
Uint16 _BA_NPRIQ;													//浼犳劅鍣ㄦ祴閲忕綉鍘媞
//Uint16 _BA_EXCID;													//浼犳劅鍣ㄦ祴閲忕綉鍘媎
//Uint16 _BA_EXCIQ;
Uint16 _BA_SCRIA;													//SCR鐢垫祦a	20110906
Uint16 _BA_SCRIB;													//SCR鐢垫祦b	20110906
Uint16 _BA_TLAC;
Uint16 _BA_TLDUDT;
Uint16 _BA_TNSKIIP;
Uint16 _BA_TMSKIIP;
Uint16 _BA_STAUABD;													//瀹氬瓙鍚屾骞剁綉鍓嶅畾瀛愬墠鍚庣數鍘嬪樊
Uint16 _BA_STAUBCD;													//瀹氬瓙鍚屾骞剁綉鍓嶅畾瀛愬墠鍚庣數鍘嬪樊
Uint16 _BA_STAIAC;													//瀹氬瓙绾跨數娴佹湁鏁堝�鏄剧ず
Uint16 _BA_STAIBA;													//瀹氬瓙绾跨數娴佹湁鏁堝�鏄剧ず
Uint16 _BA_PSTA;
Uint16 _BA_PNPR;
Uint16 _BA_PGRID;
Uint16 _BA_QSTA;
Uint16 _BA_QNPR;
Uint16 _BA_QGRID;
Uint16 _BA_SSTA;
Uint16 _BA_SNPR;
Uint16 _BA_SGRID;

Uint16 _SC_NPR_TLOV;
Uint16 _SC_MPR_TLOV;
Uint16 _SC_LVUDC1;
Uint16 _SC_LVUDC2;
Uint16 _SC_LVIAC2;
Uint16 _SC_TSCRON;
Uint16 _SC_MPR_UD;
Uint16 _SC_MPR_UQ;
Uint16 _SC_MSPEED1;
Uint16 _SC_MSPEED2;
Uint16 _SC_UDSTAC;
Uint16 _SCIB_BAUD;													//485娉㈢壒鐜�
Uint16 _SC_SKPTOV;
Uint16 _SC_FREQ1;
Uint16 _SC_FREQ2;
 
//-----------------------娴嬭瘯鐢ㄥ彉閲�----------------------------------------------------------
int16 	zys[4];			//DA鍙橀噺
Uint16 	daindex[4]; 	//BJTULVRT201204


//int32 	zys = 0;
//int16 	zys1,zys2,zys3,zys4;
Uint32 	i_cnt1=0;  //鐢ㄤ簬CCS娉㈠舰鏄剧ず
Uint32 	i_cnt2=0;  //鐢ㄤ簬CCS娉㈠舰鏄剧ず
Uint32 	i_cnt3=0;  //鐢ㄤ簬CCS娉㈠舰鏄剧ず
float   draw1[150]={0.0},draw2[150]={0.0},draw3[150]={0.0},draw4[150]={0.0},draw5[150]={0.0};
float   draw6[150]={0.0};//,draw7[100]={0.0},draw8[100]={0.0},draw9[100]={0.0},draw10[100]={0.0};
Uint16 zsector = 0;
float testtheta;

Uint16 temp_flag3;		//120507
Uint16 TX_SPEED;		//120507

Uint16	state_n=0;		//110818
Uint16	state_m=0;		//110818
Uint16	action1=0;		//110818
Uint16	action2=0;		//110818

//----------20121103鏂版坊鍔犲彉閲�-------------
float   GRD_Ut;
float   GRD_Utlv;		//201205LVRTatZB
float   kq;
Uint16	CNT_SCRON;		//20120602
float   Te_instant;
float   Te_instant2;
float   Te_instant3;

//---------20121210----------
float   lv_ctrl1=0;
float   lv_ctrl2=0;
float   lv_ctrl3=0;
float   lv_ctrl4=0;
float   lv_ctrl5=0;
float   lv_ctrl6=0;

//----20130225atsp----
float   kq_lv;
float   NGS_Udq_p_lv;
float   Te_feedback_lv;                    //瀹為檯杞煩鍊煎弽棣�
Uint16	scrdone=0;		//20130222
Uint16	scrhold=0;		//20130223
Uint16	scroff1=0;		//20130303
Uint16	cnt_lv_clrerram=0;		//20130303

//--------------------
//---------20130801---------
Uint16	ecpostep1 = 0;
Uint16	ecpostep2 = 0;
Uint16	ecpostep3 = 0;

//------------------------璋冭瘯鐘舵�杞紑鍏�----------------------------------------------
//#define	ON					1				          //寮�
//#define	OFF					0				          //鍏�
//#define	DEBUG_OPER			OFF			              //1=涓嶅甫鎿嶄綔鍣�009.6.24
extern Uint16 DEBUG_OPER;                                        //20100401at27

//鐢垫満鍙傛暟璁惧畾2010atcpc
extern float  	MPR_Ls;	 	    				//瀹氬瓙鑷劅	--鍗曚綅H
extern float	MPR_Lr;	 	    				//杞瓙鑷劅	--鍗曚綅H
extern float 	MPR_Lm;	 	    				//瀹氳浆瀛愪簰鎰�-鍗曚綅H
extern float 	MPR_Rs;	     					//瀹氬瓙鐢甸樆	--鍗曚綅ohm
extern float 	MPR_Rr;	    					//杞瓙鐢甸樆	--鍗曚綅ohm
extern float 	SIGMA;							//(1-MPR_Lm*MPR_Lm/(MPR_Ls*MPR_Lr))
extern float	STAROTRTO;       				//瀹氳浆瀛愬彉姣�
extern float	STAROTRTO2;       				//瀹氳浆瀛愬彉姣旂殑骞虫柟
extern float	POLEPAIRES;       				//鐢垫満鏋佸鏁�

//------------------------------------const瀹氫箟--------------------------------------------
//eeprom浣嶆搷浣�
const  Uint16 ONEBYTE[8]={0x0080,0x0040,0x0020,0x0010,0x0008,0x0004,0x0002,0x0001};

//AD1544閫氶亾閫夋嫨
const  Uint16 AD1544[4]={0x0000,0x2000,0x4000,0x6000};

//--------------------------------------鍙橀噺瀹氫箟-------------------------------------------
Uint16	flag[16];													//鏍囧織浣嶅彉閲�
//Uint16	disp[15];													//鏍囧織鍙橀噺

//---2013-12-13--ZZJ澧炲姞鐢垫満鍔辩
//------------------------鐢垫満鍔辩鍙傛暟璇嗗埆MagnetCurve200909------------------------------------
float   MC_y_test;
float   MC_U_test;
float	Uns_ft;
Uint16	MC_N_test;
Uint32	MC_F_cnt;
//---2013-12-13--ZZJ澧炲姞鐢垫満鍔辩

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif

//===========================================================================
// No more.
//===========================================================================
