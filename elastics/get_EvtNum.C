void get_EvtNum(Int_t runNum = 0, Int_t numEvts = 0, TString spec = ""){

  if(runNum==0){
  
  	cout << "Please enter run number ...\n";
  	cin >> runNum;
  }
  
  if(numEvts==0){
  
  	cout << "Please enter number of events in replay ...\n";
  	cin >> numEvts;
  }

  if(spec==""){
  
  	cout << "Please pick a spectrometer ...\n";
  	cin >> spec;
  }

  TString rootfile = "../../ROOTfiles/KaonLT_" + spec + Form("_coin_replay_production_%i_%i",runNum,numEvts);

  TString outputhist;
  outputhist = rootfile + ".root";
  
  TFile *f = TFile::Open(outputhist);
  if( !f || f->IsZombie()){
	return;
  }
  
  TString wLeaf;
  
  TTreeReader r("T", f);
  
  if(spec == "hms"){
  wLeaf = "H.kin.W2";
  // deltaLeaf = "H.gtr.dp";
  }else{
  wLeaf = "P.kin.W2";   
  } 
  
  TTreeReaderValue<Double_t> invMass(r, wLeaf);
  //TTreeReaderValue<Double_t> hsdelta(r,deltaLeaf);
  
  TCanvas *c1 = new TCanvas("c1","W^2", 600, 400); 
  TH1F *h1 = new TH1F("h1","W^2", 200, 0, 2);
  
  //GAUS = [Constant]*exp(-0.5*((x-[Mean])/[Sigma])*((x-[Mean])/[Sigma]))",0,2);
  
  Double_t par[6];
  
  Double_t x0,xf;
  
  x0 = 0.4;
  xf = 1.3;
  
  TF1 *g1 = new TF1("g1","gaus",0,2);
  
  TF1 *g2 = new TF1("g2","gaus",x0,xf);
  
  TF1 *g3 = new TF1("g3","gaus(3)-gaus(0)",x0,xf);
  
  if(spec == "hms"){
    while(r.Next()){
  
      int k;
      //cout << "While loop W^2 " << k << '\n';
      
      //	if(*hsdelta > -8 && *hsdelta < 8
      //   ){
      
      h1->Fill(*invMass);
      
      k++;
      //}
      
    }
  }else{
    while(r.Next()){
      
      int k;
      //cout << "While loop W^2 " << k << '\n';
      
      //	if(*ssdelta > -8 && *ssdelta < 8
      //   ){
      
      h1->Fill(*invMass);
      
      k++;
      //}
      
    }
  }

  h1->Draw();
  
  h1->Fit(g1,"R");
  
  h1->Fit(g2,"R+");
  
  //GAUS->SetParameters(Constant,Mean,Sigma);
  
  g1->GetParameters(&par[0]);
  
  g2->SetLineColor(3);
  g2->GetParameters(&par[3]);
  
  g3->SetLineColor(4);
  g3->SetParameters(par);  
  
  h1->Fit(g3,"R+");
  
  cout << "The number of events were " << g3->Integral(0,2)/0.02 << '\n';

  c1->Print(spec + "_" + Form("%i",runNum) + ".png");

  const string sep = " |";
  const int total_width = 154;
  const string line = sep+ string(total_width-1,'-') + '|';

  ofstream myfile;

  myfile.open("OUTPUT/numEvts_hms.txt", fstream::app);
  
  /*  	myfile << line << '\n'
	       << line << '\n' << sep
	       << setw(12) << left << "Run Number" << sep
	       << setw(12) << left << "Spec" << sep
	       << setw(12) << left << "Number of Events" << sep << '\n' << line << '\n'; */
       myfile << sep << setw(12) << left << runNum << sep
	       << setw(12) << left <<  spec << sep
      	       << setw(12) << left << g3->Integral(0,2)/0.02 << sep << '\n';
	 


}
