void plot_Stat_shms(Int_t runNum = 0, Int_t numEvts = 0){

  if(runNum==0){
  
  	cout << "Please enter run number ...\n";
  	cin >> runNum;
  }
  
  if(numEvts==0){
  
  	cout << "Please enter number of events in replay ...\n";
  	cin >> numEvts;
  }

  TString spec = "shms";

  TString rootfile = "../ROOTfiles/" + spec + "_coin_replay_elastics_" + Form("%i",(Int_t)runNum) + "_" + Form("%i",(Int_t)numEvts);
  // TString rootfile = "../mkjones/" + spec + "_matrixopt/ROOTfiles/" + spec + "_replay_matrixopt_" + Form("%i",(Int_t)runNum) + "_" + Form("%i",(Int_t)numEvts);
  // TString rootfile = "ROOTfiles/" + spec + "_coin_replay_production_" + Form("%i",(Int_t)runNum) + "_" + Form("%i",(Int_t)numEvts);

  TString outputhist;
  outputhist = rootfile + ".root";
  
  TFile *f = TFile::Open(outputhist);
  if( !f || f->IsZombie()){
	return;
  }
  
  TString xfpLeaf, yfpLeaf, deltaLeaf,xptarLeaf, yptarLeaf;
  
  TTreeReader r("T", f);
  
  xfpLeaf = "P.dc.x_fp";
  yfpLeaf = "P.dc.y_fp";
  xptarLeaf = "P.gtr.th";
  yptarLeaf = "P.gtr.ph";
  deltaLeaf = "P.gtr.dp";
  
  TTreeReaderValue<Double_t> xfp(r, xfpLeaf);
  TTreeReaderValue<Double_t> yfp(r, yfpLeaf);
  TTreeReaderValue<Double_t> xptar(r, xptarLeaf);
  TTreeReaderValue<Double_t> yptar(r, yptarLeaf);
  TTreeReaderValue<Double_t> ssdelta(r,deltaLeaf);
  
  TCanvas *c1 = new TCanvas("c1","Stat plots", 600, 400); 
  TH2F *h1 = new TH2F("h1","Xfp vs Yfp", 200,-50, 50,200,-50, 50);
  TH2F *h2= new TH2F("h2","Xptar vs Yptar", 200, -0.1, 0.1,200,-0.1, 0.1);
  
  
  while(r.Next()){
  
  	int k;
        cout << "While loop W^2 " << k << '\n';
	
		if(*ssdelta > -10 && *ssdelta < 15
	  ){

	h1->Fill(*yfp,*xfp);
	h2->Fill(*yptar,*xptar);
  
	   k++;
	   }
  
  }

  h1->GetXaxis()->SetTitle("yfp");
  h1->GetYaxis()->SetTitle("xfp");

  h2->GetXaxis()->SetTitle("yptar");
  h2->GetYaxis()->SetTitle("xptar");

  c1->Divide(2,1);
  c1->cd(1);  
  h1->Draw("Colz");
  c1->cd(2);
  h2->Draw("Colz");

  c1->Print("OUTPUT/pngFiles/" + spec + "_statsPlots_" + Form("%i",(int)runNum) + ".png");

  const string sep = " |";
  const int total_width = 154;
  const string line = sep+ string(total_width-1,'-') + '|';

  ofstream myfile;

}
