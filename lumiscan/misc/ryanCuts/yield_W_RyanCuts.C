int yield_W_RyanCuts(Int_t RunNumber=0){
  
  if(RunNumber == 0) {
    cout << "Enter a Run Number (-1 to exit): ";
    cin >> RunNumber;
    if( RunNumber<=0 ){
    	cerr << "...Invalid entry\n";
      	exit;
    }
  }
   const char* ROOTFileNamePattern = "$HOME/Analysis/hallc_replay/ROOTfiles/hms_replay_production_all_%d_-1.root";
   TString ROOTFileName = Form(ROOTFileNamePattern, RunNumber);
   TString rNumber = Form("%d",RunNumber);  
  
  TChain *T=new TChain("T");
  T-> Add(ROOTFileName); 
  Int_t N1= T->GetEntries();
  //TSH->StartViewer();

  TCut cTrotta = "";
  //TCut cCuts = "hcer_npe>0.5 && hsshtrk>0.7 && hsdelta>-8.5 && hsdelta<8.5 && hsxptar>-0.09 && hsxptar<0.09 && hsyptar>-0.055 &&  		hsyptar<0.055 && hsytar>-3.5 && hsytar<3.5";
  TCut cCuts = "H.tr.beta<1.2 && H.tr.beta>0.8 && H.tr.chi2>25.0 && H.tr.ndof>-8.0 && H.tr.ndof<8.0 && H.cal.etotnorm>0.6 && H.tr.tg_th>-0.080 && H.tr.tg_th<0.080 && H.tr.tg_ph>-0.035 && H.tr.tg_ph<0.035";

 TH1F *h1 = new TH1F("h1","W Cuts for " + rNumber, 200, -20, 20);
 TCanvas *c0 = new TCanvas("c0","c0");
 
 //T->Draw("H.kin.W>>h1");
 T->Draw("H.kin.W>>h1", cCuts); 

 
//*/
//title of axes
//h1->GetXaxis()->SetTitle("W (GeV)");
h1->GetYaxis()->SetTitle("H.kin.W"); 
h1->SetLineColor(2);

/*
//legend
leg = new TLegend(0.1,0.9,0.38,0.8);
//leg->SetBorderSize(0);
leg->AddEntry(h1, "Q^{2}=3.0 GeV^{2} #epsilon = 0.8800", "l");
leg->AddEntry(h1a, "Q^{2}=3.0 GeV^{2} #epsilon = 0.6070", "l");
leg->Draw();
*/

gStyle->SetOptStat(0); //gets rid of the annoying box


cout << "Integrate: " << h1->Integral() << endl;

ofstream myfile;
  myfile.open ("eltrackEvts_RyanCuts", fstream::app);
  myfile << rNumber << " " << h1->Integral() <<"\n"; //write to file
  myfile.close();


//c0->Print("yield_W_"+ rNumber + ".png");
c0->Print("yield_W_RyanCuts_"+ rNumber + ".png");


  return 0;
    }

