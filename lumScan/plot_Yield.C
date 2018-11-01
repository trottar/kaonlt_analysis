void plot_Yield(Int_t numRuns = 0){
  
//User input number of runs
  if(numRuns==0){
  	cout << "\nPlease enter number of runs... ";
  	cin >> numRuns;

  	if(numRuns==0){
		cerr << "Invalid entry\n";
		exit;

  	}
  }


  // cout << "\n~~~~~~~PLEASE MAKE SURE READ IN FILE IS IN NUMERICAL ORDER!~~~~~~~\n";

//User selection of target
  Int_t targetType;  
  

  cout << "\nPlease select target... \n" << '\n' << left << "1-Carbon\n" << left << "2-LH2\n" << left << "3-LD2\n" << '\n';
	cout << "-> ";
  	cin >> targetType;

  if(targetType==1||targetType==2||targetType==3)
	cout << " " << '\n';

  else{
	cerr << "Invalid entry\n";
	exit(0);

  }

  //Define structure for input                                                                        
  struct input_t                                                                                      
  {                                                                                                   
    Int_t   run_num;                                                                                    
    Double_t HMS_EVENTS;
    Double_t HMS_EVENTSun;
    Double_t SHMS_EVENTS;
    Double_t SHMS_EVENTSun;
    Double_t HMS_track;                                                                                    
    Double_t HMS_trackun;
    Double_t HMS_etrack;                                                                                    
    Double_t HMS_etrackun;
    Double_t SHMS_track;                                                                                    
    Double_t SHMS_trackun;
    Double_t SHMS_hadtrack;                                                                                    
    Double_t SHMS_hadtrackun;
    Double_t SHMS_pitrack;                                                                                    
    Double_t SHMS_pitrackun;
    Double_t SHMS_Ktrack;                                                                                    
    Double_t SHMS_Ktrackun;
    Double_t SHMS_ptrack;                                                                                    
    Double_t SHMS_ptrackun;
    Double_t ACC_EDTM;
    Double_t PS1;
    Double_t PS3;
    Double_t TIME;
    Double_t BCM4B;
    Double_t TRIG1;
    Double_t TRIG3;
    Double_t comp_time;                                                                                
    Double_t comp_uncer;                                                                               
    Double_t HMS_elec;                                                                                
    Double_t HMS_elecun;                                                                               
    Double_t SHMS_elec;                                                                                
    Double_t SHMS_elecun;
    Double_t SENT_EDTM;
  };                                                                                                  
                                                                                                        
  input_t  input;
 
  FILE *fp = fopen("yieldVar","r");
  char line[400];
 
  Int_t runNumber[numRuns];
  Double_t charge[numRuns];
  Double_t time[numRuns];
  Double_t current[numRuns];
  Double_t cpuLT[numRuns];
  Double_t cpuLT_uncer[numRuns];  

  Double_t counts_HMS[numRuns];
  Double_t counts_HMS_uncer[numRuns];
  Double_t eLT_HMS[numRuns];
  Double_t eLT_HMS_uncer[numRuns];
  Double_t etrEff_HMS[numRuns];
  Double_t etrEff_HMS_uncer[numRuns];
  Double_t ps3[numRuns];

  Double_t counts_SHMS[numRuns];
  Double_t counts_SHMS_uncer[numRuns];
  Double_t eLT_SHMS[numRuns];
  Double_t eLT_SHMS_uncer[numRuns];
  Double_t hadtrEff_SHMS[numRuns];
  Double_t hadtrEff_SHMS_uncer[numRuns];
  Double_t ps1[numRuns];


  Int_t goodRuns[numRuns];
  Int_t bad = 0;
  Int_t good = 0;
  Int_t tmp = 0;

  Double_t uncerEvts_HMS[numRuns], yield_HMS[numRuns], yieldRel_HMS[numRuns];
  Double_t uncerEvts_SHMS[numRuns], yield_SHMS[numRuns], yieldRel_SHMS[numRuns];

  Double_t adjCurrent[numRuns], rate_HMS[numRuns], rate_SHMS[numRuns];

//Pointers referencing column in ascii files

  TString foutname;
  Int_t j=0;
  
  for(Int_t i;fgets(&line[0],500,fp);i++) {
    if (line[0] == '#')
      {
	continue;
      }
    else
      {                                                                                             
	sscanf(&line[0],"%d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
	       &input.run_num,
	       &input.HMS_EVENTS,
	       &input.HMS_EVENTSun,
	       &input.SHMS_EVENTS,
	       &input.SHMS_EVENTSun,
	       &input.HMS_track,
	       &input.HMS_trackun,
	       &input.HMS_etrack,
	       &input.HMS_etrackun,
	       &input.SHMS_track,
	       &input.SHMS_trackun,
	       &input.SHMS_hadtrack,
	       &input.SHMS_hadtrackun,
	       &input.SHMS_pitrack,
	       &input.SHMS_pitrackun,
	       &input.SHMS_Ktrack,
	       &input.SHMS_Ktrackun,
	       &input.SHMS_ptrack,
	       &input.SHMS_ptrackun,
	       &input.ACC_EDTM,
	       &input.PS1,
	       &input.PS3,
	       &input.TIME,
	       &input.BCM4B,
	       &input.TRIG1,
	       &input.TRIG3,
	       &input.comp_time,
	       &input.comp_uncer,
	       &input.HMS_elec,
	       &input.HMS_elecun,
	       &input.SHMS_elec,
	       &input.SHMS_elecun,
	       &input.SENT_EDTM);   


      }

  
 
     runNumber[j] = input.run_num;
     charge[j] = input.BCM4B;
     time[j] = input.TIME;
     cpuLT[j] = input.comp_time;
     cpuLT_uncer[j] = input.comp_uncer;

     counts_HMS[j] = input.HMS_EVENTS;
     counts_HMS_uncer[j] = input.HMS_EVENTSun;
     eLT_HMS[j] = input.HMS_elec;
     eLT_HMS_uncer[j] = input.HMS_elecun;
     etrEff_HMS[j] = input.HMS_etrack;
     etrEff_HMS_uncer[j] = input.HMS_etrackun;
     ps3[j] = input.PS3;

     counts_SHMS[j] = input.SHMS_EVENTS;
     counts_SHMS_uncer[j] = input.SHMS_EVENTSun;
     eLT_SHMS[j] = input.SHMS_elec;
     eLT_SHMS_uncer[j] = input.SHMS_elecun;
     hadtrEff_SHMS[j] = input.SHMS_ptrack;
     hadtrEff_SHMS_uncer[j] = input.SHMS_ptrackun;
     ps1[j] = input.PS1;
 
     j++;
 }

   
  
cout << "\n````````````````````````````````````````````````````````````````````````````````````````````\n";


        for(Int_t i=0;i<numRuns;i++){	 
	  	current[i] = charge[i]/time[i];
		rate_HMS[i] = counts_HMS[i]/time[i];
		rate_SHMS[i] = counts_SHMS[i]/time[i];
		cout << runNumber[i] << " ";
	}


  	foutname = "plot_YieldvsCurrent_";

//Calculates yield for good cherenkov with and without track cuts
 
   	for(Int_t i=0;i<numRuns;i++){
	  yield_HMS[i] = (counts_HMS[i]*ps3[i])/(charge[i]*cpuLT[i]*etrEff_HMS[i]);
	  yield_SHMS[i] = (counts_SHMS[i]*ps1[i])/(charge[i]*cpuLT[i]*hadtrEff_SHMS[i]);


	}

   cout << "\nPlotting Run Numbers..." << "\n\n";

//Calculates relative yield and uncertainties & creates array to store current values for input runs
   for(Int_t i=0;i<numRuns;i++){
	adjCurrent[i]=current[i];

  	yieldRel_HMS[i] = yield_HMS[i]/yield_HMS[0];
  	yieldRel_SHMS[i] = yield_SHMS[i]/yield_SHMS[0];

	uncerEvts_HMS[i]= yield_HMS[i]/((TMath::Sqrt(counts_HMS[i]))*ps3[i]);
	uncerEvts_SHMS[i]= yield_SHMS[i]/((TMath::Sqrt(counts_SHMS[i]))*ps1[i]);
  	//uncerEvts[i] = 0;

  	cout << runNumber[i] << " ";
   }

   TString target;
   
//Graphs relative yield vs current
   
   //Error on TCanvas
   TCanvas *c1 = new TCanvas("c1","Carbon, YvC");
   //gStyle->SetOptStat(0);
   c1->Divide(2,1,0.001,0.01);
   c1->SetFillColor(42);
   //c1->SetGrid();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   
   TPad *p1 = new TPad("p1", " ",0,0,1,1);
   TPad *p1a = new TPad("p1a", " ",0,0,1,1);

   TGraphErrors *gr1 = new TGraphErrors(numRuns,current,yieldRel_HMS,0,uncerEvts_HMS);
   TGraphErrors *gr1a = new TGraphErrors(numRuns,rate_HMS,yieldRel_HMS,0,uncerEvts_HMS);
   //gr1->SetLineColor(2);
   //gr1->SetLineWidth(2);
   //gr1->GetYaxis()->SetRangeUser(0,2);
   //gr1->GetXaxis()->SetRangeUser(0,current[0]);

   	if(targetType == 1){
   		gr1->SetTitle("HMS Carbon;Current [uA];Rel. Yield");
		target = "Carbon";

   	}else if(targetType == 2){
		gr1->SetTitle("HMS LH2;Current [uA];Rel. Yield");
		target = "LH2";

   	}else{
		gr1->SetTitle("HMS LD2;Current [uA];Rel. Yield");
		target = "LD2";

	}

   gr1->GetYaxis()->SetTitleOffset(1.2);
   gr1->SetMarkerColor(4);
   gr1->SetMarkerStyle(20);
   gr1->GetXaxis()->SetTitleColor(4);
   gr1->GetXaxis()->SetLabelColor(4);

   gr1a->SetMarkerColor(2);
   gr1a->SetMarkerStyle(20);

   Double_t xmin1 = gr1a->GetXaxis()->GetXmin();
   Double_t xmax1 = gr1a->GetXaxis()->GetXmax();
   Double_t dx = (xmax1 - xmin1)/0.8;

   Double_t ymin1 = gr1a->GetYaxis()->GetXmin();
   Double_t ymax1 = gr1a->GetYaxis()->GetXmax();

   Double_t dy = (ymax1 - ymin1)/0.8;

   c1->cd(1);
   //p1->SetTopMargin(0);
   //p1->SetBottomMargin(0);
   //p1->SetRightMargin(0);
   p1->SetGrid();
   p1a->SetFillStyle(4000);
   p1->Draw();
   p1->cd();

   gr1->Draw("AP");
   gPad->Update();
   
   p1a->Range(xmin1-0.1*dx, ymin1-0.1*dy, xmax1+0.1*dx, ymax1+0.1*dy);
   p1a->Draw();
   p1a->cd();

   gr1a->Draw("P");
   gPad->Update();
   
   TGaxis *a1 = new TGaxis(xmin1, ymax1, xmax1, ymax1, xmin1, xmax1, 510, "-L");
   a1->SetTitle("Rates [Hz]");
   a1->SetTitleColor(2);
   a1->SetLabelColor(2);
   a1->SetNdivisions(6);
   a1->Draw();
   gPad->Update();

   TLine *l = new TLine(xmin1,1.,xmax1,1.);
   l->SetLineColor(kRed);
   //l->SetLineWidth(2);
   l->Draw("lsame");
   gPad->Update();

   TPad *p2 = new TPad("p2", " ",0,0,1,1);
   TPad *p2a = new TPad("p2a", " ",0,0,1,1);

   TGraphErrors *gr2 = new TGraphErrors(numRuns,current,yieldRel_SHMS,0,uncerEvts_SHMS);
   TGraphErrors *gr2a = new TGraphErrors(numRuns,rate_SHMS,yieldRel_SHMS,0,uncerEvts_SHMS);
   //gr2->SetLineColor(2);
   //gr2->SetLineWidth(2);
   //gr2->GetYaxis()->SetRangeUser(0,2);
   //gr2->GetXaxis()->SetRangeUser(0,current[0]);

   	if(targetType == 1){
   		gr2->SetTitle("SHMS Carbon;Current [uA];Rel. Yield");

   	}else if(targetType == 2){
		gr2->SetTitle("SHMS LH2;Current [uA];Rel. Yield");

   	}else{
		gr2->SetTitle("SHMS LD2;Current [uA];Rel. Yield");

	}

   gr2->GetYaxis()->SetTitleOffset(1.2);	
   gr2->SetMarkerColor(4);
   gr2->SetMarkerStyle(20);
   gr2->GetXaxis()->SetTitleColor(4);
   gr2->GetXaxis()->SetLabelColor(4);

   gr2a->SetMarkerColor(2);
   gr2a->SetMarkerStyle(20);

   Double_t xmin2 = gr2a->GetXaxis()->GetXmin();
   Double_t xmax2 = gr2a->GetXaxis()->GetXmax();
   Double_t dx2 = (xmax2 - xmin2)/0.8;

   Double_t ymin2 = gr2a->GetYaxis()->GetXmin();
   Double_t ymax2 = gr2a->GetYaxis()->GetXmax();

   Double_t dy2 = (ymax2 - ymin2)/0.8;

   c1->cd(2);
   //p2->SetTopMargin(0);
   //p2->SetBottomMargin(0);
   //p2->SetLeftMargin(0);
   p2->SetGrid();
   p2a->SetFillStyle(4000);
   p2->Draw();
   p2->cd();

   gr2->Draw("AP");
   gPad->Update();
   
   p2a->Range(xmin2-0.1*dx2, ymin2-0.1*dy2, xmax2+0.1*dx2, ymax2+0.1*dy2);
   p2a->Draw();
   p2a->cd();

   gr2a->Draw("P");
   gPad->Update();
   
   TGaxis *a2 = new TGaxis(xmin2, ymax2, xmax2, ymax2, xmin2, xmax2, 510, "-L");
   a2->SetTitle("Rates [Hz]");
   a2->SetTitleColor(2);
   a2->SetLabelColor(2);
   a2->SetNdivisions(6);
   a2->Draw();
   gPad->Update();

   TLine *l2 = new TLine(xmin2,1.,xmax2,1.);
   l2->SetLineColor(kRed);
   //l->SetLineWidth(2);
   l2->Draw("lsame");
   gPad->Update();
   
   // values for controlling format
   const string sep = " |" ;
   const int total_width = 212;
   const string tab = string( total_width-1, '-' ) + '|' ;

//Creates a table with various variables listed below  

   ofstream myfile;




   myfile.open ("OUTPUT/LuminosityScans.txt", fstream::app);

    	myfile << tab << '\n'
    	       << " |Rates, Target " << target << "| Run Numbers ";

	for(Int_t i=0;i<numRuns-1;i++)
	  myfile << runNumber[i] << ", ";

	myfile << runNumber[numRuns-1] << "| " << '\n'
	       << setw(12) << "-> Applied Cuts HMS: [Applied Cuts:[[Beta>0.8, Beta<1.3, Ecal>0.6, Ecal<2.0, CernpeSum>0.5, |Hms delta|<8, xptar>0.08 , yptar>0.035]]" << '\n'
    	       << tab << '\n' << sep
    	       << setw(12) << left << "RunNumber" << sep
  	       << setw(12) << left << "Current" << sep
  	       << setw(12) << left << "BeamTime" << sep
  	       << setw(12) << left << "Charge" << sep
  	       << setw(12) << left << "HMS count" << sep
  	       << setw(12) << left << "+/-" << sep
  	       << setw(12) << left << "Rate[Hz]" << sep
  	       << setw(12) << left << "PS3" << sep
  	       << setw(12) << left << "Yield_HMS" << sep
  	       << setw(12) << left << "RelY_HMS" << sep 
 	       << setw(12) << left << "Uncer_HMS" << sep 
	  //<< setw(12) << left << "eLT_HMS" << sep
  	       << setw(12) << left << "TrEff_HMS" << sep
  	       << setw(12) << left << "+/-" << sep
  	       << setw(12) << left << "CPULT" << sep 
  	       << setw(12) << left << "+/-" << sep << '\n' << tab << '\n';
  
   for(Int_t i=0;i<numRuns;i++){
  	myfile << sep << setw(12) << runNumber[i] << sep
  	       << setw(12) << current[i] << sep
  	       << setw(12) << time[i] << sep
  	       << setw(12) << charge[i] << sep
  	       << setw(12) << counts_HMS[i] << sep
  	       << setw(12) << counts_HMS_uncer[i] << sep
  	       << setw(12) << rate_HMS[i] << sep
  	       << setw(12) << left << ps3[i] << sep
  	       << setw(12) << yield_HMS[i] << sep
  	       << setw(12) << yieldRel_HMS[i] << sep
 	       << setw(12) << uncerEvts_HMS[i] << sep
	  //<< setw(12) << eLT_HMS[i] << sep
  	       << setw(12) << etrEff_HMS[i] << sep
  	       << setw(12) << etrEff_HMS_uncer[i] << sep
  	       << setw(12) << cpuLT[i] << sep
  	       << setw(12) << cpuLT_uncer[i] << sep << '\n';
   }


	myfile << tab << '\n' << sep
	       << setw(12) << "-> Applied Cuts SHMS: [Applied Cuts:[[Beta>0.5, Beta<1.4, Ecal<0.6, HGnpeSum<1.5, AeornpeSum<1.5, Shms delta>-10, Shms delta<20, xptar>0.08 , yptar>0.035]]" << '\n'
    	       << tab << '\n' << sep
    	       << setw(12) << left << "RunNumber" << sep
  	       << setw(12) << left << "Current" << sep
  	       << setw(12) << left << "BeamTime" << sep
  	       << setw(12) << left << "Charge" << sep
  	       << setw(12) << left << "SHMS count" << sep
  	       << setw(12) << left << "+/-" << sep
  	       << setw(12) << left << "Rate[Hz]" << sep
  	       << setw(12) << left << "PS1" << sep
	       << setw(12) << left << "Yield_SHMS" << sep
  	       << setw(12) << left << "RelY_SHMS" << sep 
 	       << setw(12) << left << "Uncer_SHMS" << sep
	  //<< setw(12) << left << "eLT_SHMS" << sep
  	       << setw(12) << left << "TrEff_SHMS" << sep
  	       << setw(12) << left << "+/-" << sep
  	       << setw(12) << left << "CPULT" << sep 
  	       << setw(12) << left << "+/-" << sep << '\n' << tab << '\n';
  
   for(Int_t i=0;i<numRuns;i++){
  	myfile << sep << setw(12) << runNumber[i] << sep
  	       << setw(12) << current[i] << sep
  	       << setw(12) << time[i] << sep
  	       << setw(12) << charge[i] << sep
   	       << setw(12) << counts_SHMS[i] << sep
   	       << setw(12) << counts_SHMS_uncer[i] << sep
  	       << setw(12) << rate_SHMS[i] << sep
  	       << setw(12) << left << ps1[i] << sep
  	       << setw(12) << yield_SHMS[i] << sep
  	       << setw(12) << yieldRel_SHMS[i] << sep
 	       << setw(12) << uncerEvts_SHMS[i] << sep
	  //<< setw(12) << eLT_SHMS[i] << sep
  	       << setw(12) << hadtrEff_SHMS[i] << sep
  	       << setw(12) << hadtrEff_SHMS_uncer[i] << sep
  	       << setw(12) << cpuLT[i] << sep
  	       << setw(12) << cpuLT_uncer[i] << sep <<  '\n';
   }

        myfile << tab << '\n';

   myfile.close();


//Prints an image file of the plot
   c1->Print("OUTPUT/" + foutname + target + Form("_%i",runNumber[0]) + Form("-%i",runNumber[numRuns-1]) + "_rates.png");

   return;


}
