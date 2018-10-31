void plot_YvC(){
  
//User input number of runs
  /*if(numRuns==0){
  	cout << "\nPlease enter number of runs... ";
  	cin >> numRuns;

  	if(numRuns==0){
		cerr << "Invalid entry\n";
		exit;

  	}
  }*/


  cout << "\n~~~~~~~PLEASE MAKE SURE READ IN FILE IS IN NUMERICAL ORDER!~~~~~~~\n";

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

//User input of run numbers

  TString runInputs = "runInputs";

  TTree *inAsc = new TTree("inAsc", "inAsc");
  Int_t numRuns = inAsc->ReadFile(runInputs,"runNumber");
  inAsc->Draw("runNumber","","goff");

  Double_t *inputRuns = inAsc->GetV1();

  /*for(Int_t i=0;i<numRuns;i++){
  	cout << "Please enter run numbers: ";
  	cin >> inputRuns[i];

  }*/

//User selection of run type
  Int_t runType;  

  cout << "\nPlease select run type... \n" << '\n' << left << "1-Good Cerenkov and Track\n" << left << "2-Good Cerenkov\n" << '\n';
  	cout << "-> ";  
	cin >> runType;

  if(runType>2){
		cerr << "Invalid entry\n";
		exit(0);

  	}
  if(runType<=0){
		cerr << "Invalid entry\n";
		exit(0);

  	}

//Ascii files, see hms_cut.C/shms_cut.C
  TString filename1 = "yieldVar";
  TString filename2 = "efficiencies";
  TString filename3 = "tryieldVar";




//Read in of ascii files
  TTree *tr1 = new TTree("tr1", "tr1");
  Int_t ndata1 = tr1->ReadFile(filename1,"runNumber:counts:charge:current");
  tr1->Draw("runNumber:counts:charge:current","","goff");
 
  TTree *tr2 = new TTree("tr2", "tr2");
  Int_t ndata2 = tr2->ReadFile(filename2,"runNumber:cpuLT:trEff");
  tr2->Draw("runNumber:cpuLT:trEff","","goff");

  TTree *tr3 = new TTree("tr3", "tr3");
  Int_t ndata3 = tr3->ReadFile(filename3,"runNumber:counts:charge:current");
  tr3->Draw("runNumber:counts:charge:current","","goff");
  
  Double_t *runNumber = tr1->GetV1();
  Double_t *counts;
  Double_t *charge;
  Double_t *current;
  Double_t *cpuLT;
  Double_t *trEff;
  Int_t goodRuns[numRuns];
  Int_t bad = 0;
  Int_t good = 0;
  Int_t tmp = 0;

//Pointers referencing column in ascii files

  TString foutname;

  if(runType==1){
  	counts = tr3->GetV2();
  	charge = tr3->GetV3();
  	current = tr3->GetV4();
  	cpuLT = tr2->GetV2();
  	trEff = tr2->GetV3();

  	foutname = "plot_TrackYieldvsCurrent_";

  }else{
  	counts = tr1->GetV2();
  	charge = tr1->GetV3();
  	current = tr1->GetV4();
  	cpuLT = tr2->GetV2();
  	trEff = tr2->GetV3();
  	
  	foutname = "plot_YieldvsCurrent_";

  }

//Nested loop that matches input runs with runs avaliable in ascii files
  while(tmp < numRuns){

	for(Int_t i=0;i<ndata1;i++){

		if(runNumber[i]==inputRuns[tmp] && goodRuns[tmp-1]!=i){
			cout << "\nRun number " << inputRuns[tmp] << " accepted (i)" << '\n';
			cout << i << " ~loop " << tmp << '\n';
			goodRuns[tmp]=i;
			cout << runNumber[i] << " ~ " << counts[i] << "\n";
			good++;
			break;

		}else if(i==ndata1-1){
			cout << "BAD " << i << " ~loop " << tmp << '\n';
			bad++;
			break;

		}else{
			cout << "BAD " << i << " ~loop " << tmp << '\n';
			bad++;
		}
	}

	tmp++;

  }


//Number of good and bad run number matches along with the number of while loops run 	
  if(good >= numRuns){
  	cout << '\n' << good << " good for while loop " << tmp << '\n';
  	cout << bad << " bad for while loop " << tmp << '\n';

  }else{
	cout << "\nInvalid entries found!" << '\n';
	exit(0);

  }
  
   Double_t yield[ndata1], yieldRel[ndata1], uncerEvts[ndata1], adjCurrent[ndata1];

//Calculates yield for good cherenkov with and without track cuts
   if(runType==1){  
   	for(Int_t i=0;i<numRuns;i++)
  		yield[i] = counts[goodRuns[i]]/charge[goodRuns[i]]/cpuLT[goodRuns[i]]/trEff[goodRuns[i]];

   }else{
	for(Int_t i=0;i<numRuns;i++)
  		yield[i] = counts[goodRuns[i]]/charge[goodRuns[i]]/cpuLT[goodRuns[i]];

   }
   
 
   cout << "\nPlotting Run Numbers..." << '\n';

//Calculates relative yield and uncertainties & creates array to store current values for input runs
   for(Int_t i=0;i<numRuns;i++){
	adjCurrent[i]=current[goodRuns[i]];

  	yieldRel[i] = yield[i]/yield[1];
	uncerEvts[i]= TMath::Sqrt(counts[goodRuns[i]])/yield[i];
  	//uncerEvts[i] = 0;

  	cout << runNumber[goodRuns[i]] << " ";
   }

   TString target;
   
//Graphs relative yield vs current
   
   //Error on TCanvas
   TCanvas *c1 = new TCanvas("c1","Carbon, YvC");
   //c1->SetFillColor(42);
   c1->SetGrid();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   
   TGraphErrors *gr1 = new TGraphErrors(numRuns,adjCurrent,yieldRel,0,uncerEvts);
   TLine *l = new TLine(0.,1.,70.,1.);
   l->SetLineColor(kRed);
   //l->SetLineWidth(2);
   //gr1->SetLineColor(2);
   //gr1->SetLineWidth(2);
   //gr1->GetYaxis()->SetRangeUser(0,2);
   //gr1->GetYaxis()->SetRangeUser(0.8,1);
   gr1->GetXaxis()->SetRangeUser(0,70.);

   if(runType==1){

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

   }else{

	if(targetType == 1){
   		gr1->SetTitle("Carbon;Current [uA];Rel. Yield");
		target = "carbon";

   	}else if(target == 2){
		gr1->SetTitle("LH2;Current [uA];Rel. Yield");
		target = "lh2";

   	}else{
		gr1->SetTitle("LD2;Current [uA];Rel. Yield");
		target = "ld2";

	}
   }

   gr1->SetMarkerColor(4);
   gr1->SetMarkerStyle(20);
   gr1->Draw("AP");
   l->Draw("lsame");
   c1->Update();
   
   // values for controlling format
   const string sep = " |" ;
   const int total_width = 154;
   const string line = sep + string( total_width-1, '-' ) + '|' ;

//Creates a table with various variables listed below  
   if(runType==1){

   ofstream myfile;

   myfile.open ("LuminosityScans.txt", fstream::app);

    	myfile << line << '\n'
    	       //<< setw(12) << "-> Applied Cuts:[[CerSum>0.5, |Hms delta|<8.5, Ecal>0.7, |xptar|<0.09, |yptar|<0.055, |ytar|<3.5]] (Rich's Orginal Cuts)" << '\n'
    	       << setw(12) << "-> Applied Cuts: [Applied Cuts:[[CerSum>2.0, Ecal>0.7, Ecal<1.5, |Hms delta|<8] (Rich's Orginal Cuts)]" << '\n'
    	       << line << '\n' << sep
    	       << setw(12) << left << "RunNumber" << sep
  	       << setw(12) << left << "Current" << sep
  	       //<< setw(12) << left << "BeamTime" << sep
  	       << setw(12) << left << "Charge" << sep
  	       << setw(12) << left << "TAC" << sep
  	       << setw(12) << left << "TrackYield" << sep
  	       << setw(12) << left << "RelTrackYield" << sep
  	       << setw(12) << left << "CPULT" << sep 
  	       << setw(12) << left << "TrackEff" << sep
 	       << setw(12) << left << "Uncertainty" << sep << '\n' << line << '\n';
  
   for(Int_t i=0;i<numRuns;i++){
  	myfile << sep << setw(12) << runNumber[goodRuns[i]] << sep
  	       << setw(12) << current[goodRuns[i]] << sep
  	       //<< setw(12) << bTime[goodRuns[i]] << sep
  	       << setw(12) << charge[goodRuns[i]] << sep
  	       << setw(12) << counts[goodRuns[i]] << sep
  	       << setw(12) << yield[goodRuns[i]]/1000 << sep
  	       << setw(12) << yieldRel[goodRuns[i]] << sep
  	       << setw(12) << cpuLT[goodRuns[i]] << sep
  	       << setw(12) << trEff[goodRuns[i]] << sep
 	       << setw(12) << uncerEvts[goodRuns[i]] << sep << '\n';
   }

   myfile.close();

   }else{

   ofstream myfile;

   myfile.open ("LuminosityScans.txt", fstream::app);

    	myfile << line << '\n'
    	       //<< setw(12) << "-> Applied Cuts:[[CerSum>0.5, |Hms delta|<8.5, Ecal>0.7, |xptar|<0.09, |yptar|<0.055, |ytar|<3.5]] (Rich's Orginal Cuts)" << '\n'
    	       << setw(12) << "-> Applied Cuts: [Applied Cuts:[[CerSum>2.0, Ecal>0.7, Ecal<1.5] (Rich's Orginal Cuts)]" << '\n'
    	       << line << '\n' << sep
    	       << setw(12) << left << "RunNumber" << sep
  	       << setw(12) << left << "Current" << sep
  	       << setw(12) << left << "Charge" << sep
  	       << setw(12) << left << "TAC" << sep
  	       << setw(12) << left << "Yield" << sep
  	       << setw(12) << left << "RelYield" << sep
  	       << setw(12) << left << "CPULT" << sep 
  	       << setw(12) << left << "TrackEff" << sep
 	       << setw(12) << left << "Uncertainty" << sep << '\n' << line << '\n';
  
   for(Int_t i=0;i<numRuns;i++){
  	myfile << sep << setw(12) << runNumber[goodRuns[i]] << sep
  	       << setw(12) << current[goodRuns[i]] << sep
  	       << setw(12) << charge[goodRuns[i]] << sep
  	       << setw(12) << counts[goodRuns[i]] << sep
  	       << setw(12) << yield[goodRuns[i]]/1000 << sep
  	       << setw(12) << yieldRel[goodRuns[i]] << sep
  	       << setw(12) << cpuLT[goodRuns[i]] << sep 
  	       << setw(12) << trEff[goodRuns[i]] << sep
 	       << setw(12) << uncerEvts[goodRuns[i]] << sep << '\n';
   }

   myfile.close();

   }

//Prints an image file of the plot
   c1->Print("OUTPUT/" + foutname + target + Form("_%i",(Int_t)inputRuns[0]) + Form("-%i",(Int_t)inputRuns[numRuns-1]) + ".png");

   return;

}
