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
    Double_t TRIG1;
    Double_t TRIG3;
    Double_t TIME;
    Double_t BCM4B;
    Double_t PS1;
    Double_t PS3;
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
 
  Int_t *runNumber;
  Double_t *counts;
  Double_t *charge;
  Double_t *time;
  Double_t current[numRuns];
  Double_t *cpuLT;
  Double_t *trEffHMS;
  Double_t *etrEff;
  Double_t trEff[numRuns];
  Int_t goodRuns[numRuns];
  Int_t bad = 0;
  Int_t good = 0;
  Int_t tmp = 0;
  Double_t yield[numRuns], yieldRel[numRuns], uncerEvts[numRuns], adjCurrent[numRuns];
//Pointers referencing column in ascii files

  TString foutname;


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
	       &input.TRIG1,
	       &input.TRIG3,
	       &input.TIME,
	       &input.BCM4B,
	       &input.PS1,
	       &input.PS3,
	       &input.comp_time,
	       &input.comp_uncer,
	       &input.HMS_elec,
	       &input.HMS_elecun,
	       &input.SHMS_elec,
	       &input.SHMS_elecun,
	       &input.SENT_EDTM);   
  cout << "````````````````````````````````````````````````````````````````````````````````````````````\n";
        runNumber[i] = input.run_num;
  	counts[i] = input.HMS_EVENTS;
  	charge[i] = input.BCM4B;
  	time[i] = input.TIME;
  	cpuLT[i] = input.comp_time;
	trEffHMS[i] = input.HMS_track;
  	etrEff[i] = input.HMS_etrack;

      }



  cout << input.run_num << "\n";
 
 

 }


        for(Int_t i=3;i<numRuns;i++){
	  	current[i] = charge[i]/time[i];
		cout << runNumber[i] << " ";
	}

	for(Int_t i=3;i<numRuns;i++)
	  	trEff[i] = trEffHMS[i] + etrEff[i];

  	foutname = "plot_TrackYieldvsCurrent_";

//Calculates yield for good cherenkov with and without track cuts
 
   	for(Int_t i=3;i<numRuns;i++)
  		yield[i] = counts[i]/charge[i]/cpuLT[i]/trEff[i];

   cout << "\nPlotting Run Numbers..." << "\n\n";

//Calculates relative yield and uncertainties & creates array to store current values for input runs
   for(Int_t i=3;i<numRuns;i++){
	adjCurrent[i]=current[i];

  	yieldRel[i] = yield[i]/yield[0];
	uncerEvts[i]= TMath::Sqrt(counts[i])/yield[i];
  	//uncerEvts[i] = 0;

  	cout << runNumber[i] << " ";
   }

   TString target;
   
//Graphs relative yield vs current
   
   //Error on TCanvas
   TCanvas *c1 = new TCanvas("c1","Carbon, YvC");
   //c1->SetFillColor(42);
   c1->SetGrid();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   
   TGraphErrors *gr1 = new TGraphErrors(numRuns,current,yieldRel,0,uncerEvts);
   TLine *l = new TLine(0.,1.,70.,1.);
   l->SetLineColor(kRed);
   //l->SetLineWidth(2);
   //gr1->SetLineColor(2);
   //gr1->SetLineWidth(2);
   //gr1->GetYaxis()->SetRangeUser(0,2);
   //gr1->GetYaxis()->SetRangeUser(0.8,1);
   gr1->GetXaxis()->SetRangeUser(0,70.);


   	if(targetType == 1){
   		gr1->SetTitle("Carbon;Current [uA];Rel. Track Yield");
		target = "carbon";

   	}else if(targetType == 2){
		gr1->SetTitle("LH2;Current [uA];Rel. Track Yield");
		target = "lh2";

   	}else{
		gr1->SetTitle("LD2;Current [uA];Rel. Track Yield");
		target = "ld2";

	}


   gr1->SetMarkerColor(4);
   gr1->SetMarkerStyle(20);
   gr1->Draw("AP");
   l->Draw("lsame");
   c1->Update();
   
   // values for controlling format
   const string sep = " |" ;
   const int total_width = 154;
   const string tab = sep + string( total_width-1, '-' ) + '|' ;

//Creates a table with various variables listed below  

   ofstream myfile;

   myfile.open ("LuminosityScans.txt", fstream::app);

    	myfile << tab << '\n'
    	       //<< setw(12) << "-> Applied Cuts:[[CerSum>0.5, |Hms delta|<8.5, Ecal>0.7, |xptar|<0.09, |yptar|<0.055, |ytar|<3.5]] (Rich's Orginal Cuts)" << '\n'
    	       << setw(12) << "-> Applied Cuts: [Applied Cuts:[[CerSum>2.0, Ecal>0.7, Ecal<1.5, |Hms delta|<8]]" << '\n'
    	       << tab << '\n' << sep
    	       << setw(12) << left << "RunNumber" << sep
  	       << setw(12) << left << "Current" << sep
  	       //<< setw(12) << left << "BeamTime" << sep
  	       << setw(12) << left << "Charge" << sep
  	       << setw(12) << left << "TAC" << sep
  	       << setw(12) << left << "TrackYield" << sep
  	       << setw(12) << left << "RelTrackYield" << sep
  	       << setw(12) << left << "CPULT" << sep 
  	       << setw(12) << left << "TrackEff" << sep
 	       << setw(12) << left << "Uncertainty" << sep << '\n' << tab << '\n';
  
   for(Int_t i=3;i<numRuns;i++){
  	myfile << sep << setw(12) << runNumber[i] << sep
  	       << setw(12) << current[i] << sep
  	       //<< setw(12) << bTime[i] << sep
  	       << setw(12) << charge[i] << sep
  	       << setw(12) << counts[i] << sep
  	       << setw(12) << yield[i]/1000 << sep
  	       << setw(12) << yieldRel[i] << sep
  	       << setw(12) << cpuLT[i] << sep
  	       << setw(12) << trEff[i] << sep
 	       << setw(12) << uncerEvts[i] << sep << '\n';
   }

   myfile.close();


//Prints an image file of the plot
   c1->Print("OUTPUT/" + foutname + target + Form("_%i",runNumber[0]) + Form("-%i",runNumber[numRuns-1]) + ".png");

   return;


}
