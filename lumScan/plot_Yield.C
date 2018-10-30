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

  if(targetType==1)
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

  Double_t counts_HMS[numRuns];
  Double_t eLT_HMS[numRuns];
  Double_t etrEff_HMS[numRuns];
  Double_t ps3[numRuns];

  Double_t counts_SHMS[numRuns];
  Double_t eLT_SHMS[numRuns];
  Double_t hadtrEff_SHMS[numRuns];
  Double_t ps1[numRuns];


  Int_t goodRuns[numRuns];
  Int_t bad = 0;
  Int_t good = 0;
  Int_t tmp = 0;

  Double_t uncerEvts_HMS[numRuns], yield_HMS[numRuns], yieldRel_HMS[numRuns];
  Double_t uncerEvts_SHMS[numRuns], yield_SHMS[numRuns], yieldRel_SHMS[numRuns];

  Double_t adjCurrent[numRuns];

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

     counts_HMS[j] = input.HMS_EVENTS;
     eLT_HMS[j] = input.HMS_elec;
     etrEff_HMS[j] = input.HMS_etrack;
     ps3[j] = input.PS3;

     counts_SHMS[j] = input.SHMS_EVENTS;
     eLT_SHMS[j] = input.SHMS_elec;
     hadtrEff_SHMS[j] = input.SHMS_ptrack;
     ps1[j] = input.PS1;
 
     j++;
 }

   
  
cout << "\n````````````````````````````````````````````````````````````````````````````````````````````\n";


        for(Int_t i=0;i<numRuns;i++){	 
	  	current[i] = charge[i]/time[i];
		cout << runNumber[i] << " ";
		//cout << [i] << " ";
	}


  	foutname = "plot_TrackYieldvsCurrent_";

//Calculates yield for good cherenkov with and without track cuts
 
   	for(Int_t i=0;i<numRuns;i++){
	  yield_HMS[i] = counts_HMS[i]/(charge[i]*cpuLT[i]*etrEff_HMS[i]*eLT_HMS[i]);
	  yield_SHMS[i] = counts_SHMS[i]/(charge[i]*cpuLT[i]*hadtrEff_SHMS[i]*eLT_SHMS[i]);
	}

   cout << "\nPlotting Run Numbers..." << "\n\n";

//Calculates relative yield and uncertainties & creates array to store current values for input runs
   for(Int_t i=0;i<numRuns;i++){
	adjCurrent[i]=current[i];

  	yieldRel_HMS[i] = yield_HMS[i]/yield_HMS[numRuns-1];
  	yieldRel_SHMS[i] = yield_SHMS[i]/yield_SHMS[numRuns-1];

	uncerEvts_HMS[i]= yield_HMS[i]/TMath::Sqrt(counts_HMS[i]);
	uncerEvts_SHMS[i]= yield_SHMS[i]/TMath::Sqrt(counts_SHMS[i]);
  	//uncerEvts[i] = 0;

  	cout << runNumber[i] << " ";
   }

   TString target;
   
//Graphs relative yield vs current
   
   //Error on TCanvas
   TCanvas *c1 = new TCanvas("c1","Carbon, YvC");
   c1->Divide(2,1);
   //c1->SetFillColor(42);
   c1->SetGrid();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   
   TGraphErrors *gr1 = new TGraphErrors(numRuns,current,yieldRel_HMS,0,uncerEvts_HMS);
   TLine *l = new TLine(0.,1.,70.,1.);
   l->SetLineColor(kRed);
   //l->SetLineWidth(2);
   //gr1->SetLineColor(2);
   //gr1->SetLineWidth(2);
   //gr1->GetYaxis()->SetRangeUser(0,2);
   //gr1->GetYaxis()->SetRangeUser(0.8,1);
   gr1->GetXaxis()->SetRangeUser(0,70.);


   	if(targetType == 1){
   		gr1->SetTitle("HMS Carbon;Current [uA];Rel. Track Yield");
		target = "carbon";

   	}else if(targetType == 2){
		gr1->SetTitle("HMS LH2;Current [uA];Rel. Track Yield");
		target = "lh2";

   	}else{
		gr1->SetTitle("HMS LD2;Current [uA];Rel. Track Yield");
		target = "ld2";

	}


   gr1->SetMarkerColor(4);
   gr1->SetMarkerStyle(20);
   c1->cd(1);
   gr1->Draw("AP");
   l->Draw("lsame");
   c1->Update();

   TGraphErrors *gr2 = new TGraphErrors(numRuns,current,yieldRel_SHMS,0,uncerEvts_SHMS);
   TLine *l2 = new TLine(0.,1.,70.,1.);
   l2->SetLineColor(kRed);
   //l2->SetLineWidth(2);
   //gr2->SetLineColor(2);
   //gr2->SetLineWidth(2);
   //gr2->GetYaxis()->SetRangeUser(0,2);
   //gr2->GetYaxis()->SetRangeUser(0.8,1);
   gr2->GetXaxis()->SetRangeUser(0,70.);


   	if(targetType == 1){
   		gr2->SetTitle("SHMS Carbon;Current [uA];Rel. Track Yield");
		//target = "carbon";

   	}else if(targetType == 2){
		gr2->SetTitle("SHMS LH2;Current [uA];Rel. Track Yield");
		//target = "lh2";

   	}else{
		gr2->SetTitle("SHMS LD2;Current [uA];Rel. Track Yield");
		//target = "ld2";

	}


   gr2->SetMarkerColor(4);
   gr2->SetMarkerStyle(20);
   c1->cd(2);
   gr2->Draw("AP");
   l2->Draw("lsame");
   c1->Update();
   
   // values for controlling format
   const string sep = " |" ;
   const int total_width = 154;
   const string tab = sep + string( total_width-1, '-' ) + '|' ;

//Creates a table with various variables listed below  

   ofstream myfile;

   myfile.open ("OUTPUT/LuminosityScans.txt", fstream::app);

    	myfile << tab << '\n'
    	       << setw(12) << "-> Applied Cuts: [Applied Cuts:[[CerSum>2.0, Ecal>0.7, Ecal<1.5, |Hms delta|<8]]" << '\n'
    	       << tab << '\n' << sep
    	       << setw(12) << left << "RunNumber" << sep
  	       << setw(12) << left << "Current" << sep
  	       << setw(12) << left << "BeamTime" << sep
  	       << setw(12) << left << "Charge" << sep
  	       << setw(12) << left << "HMS count" << sep
  	       << setw(12) << left << "Yield_HMS" << sep
  	       << setw(12) << left << "RelY_HMS" << sep 
  	       << setw(12) << left << "eLT_HMS" << sep
  	       << setw(12) << left << "TrEff_HMS" << sep
 	       << setw(12) << left << "Uncer_HMS" << sep 
  	       << setw(12) << left << "SHMS count" << sep
	       << setw(12) << left << "Yield_SHMS" << sep
  	       << setw(12) << left << "RelY_SHMS" << sep 
  	       << setw(12) << left << "eLT_SHMS" << sep
  	       << setw(12) << left << "TrEff_SHMS" << sep
 	       << setw(12) << left << "Uncer_SHMS" << sep
  	       << setw(12) << left << "CPULT" << sep << '\n' << tab << '\n';
  
   for(Int_t i=0;i<numRuns;i++){
  	myfile << sep << setw(12) << runNumber[i] << sep
  	       << setw(12) << current[i] << sep
  	       << setw(12) << time[i] << sep
  	       << setw(12) << charge[i] << sep
  	       << setw(12) << counts_HMS[i] << sep
  	       << setw(12) << yield_HMS[i] << sep
  	       << setw(12) << yieldRel_HMS[i] << sep
  	       << setw(12) << eLT_HMS[i] << sep
  	       << setw(12) << etrEff_HMS[i] << sep
 	       << setw(12) << uncerEvts_HMS[i] << sep
   	       << setw(12) << counts_SHMS[i] << sep
  	       << setw(12) << yield_SHMS[i] << sep
  	       << setw(12) << yieldRel_SHMS[i] << sep
  	       << setw(12) << eLT_SHMS[i] << sep
  	       << setw(12) << hadtrEff_SHMS[i] << sep
 	       << setw(12) << uncerEvts_SHMS[i] << sep
  	       << setw(12) << cpuLT[i] << sep << '\n';
   }

   myfile.close();


//Prints an image file of the plot
   c1->Print("OUTPUT/" + foutname + target + Form("_%i",runNumber[0]) + Form("-%i",runNumber[numRuns-1]) + ".png");

   return;


}
