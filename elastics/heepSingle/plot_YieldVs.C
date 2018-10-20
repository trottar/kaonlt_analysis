void plot_YieldVs(TString txtFile = ""){
  
  if (txtFile=="") {
  cout << "Please enter beam energy: ";
  cin >> txtFile;
  }
  
  TString filename1 = "heep_" + txtFile + "_Yield";
  TString filename2 = "heep_" + txtFile + "_Evts";
  TString outputpdf;
  TString foutname = "plot_" + filename1;
  outputpdf = "OUTPUT/plot_" + filename1 + ".pdf";

  TTree *tr1 = new TTree("tr1", "tr1");
  Int_t ndata1 = tr1->ReadFile(filename1,"yield:theta:momentum:simcYield");
  tr1->Draw("yield:theta:momentum:simcYield","","goff");
  
  TTree *tr2 = new TTree("tr1", "tr1");
  Int_t ndata2 = tr2->ReadFile(filename2,"evts:theta:momentum:q2");
  tr2->Draw("evts:theta:momentum:q2","","goff");
  
  Double_t *yield, * theta, *momentum, *simcYield, *evts, *q2;
  
  yield = tr1->GetV1();
  theta = tr1->GetV2();
  momentum = tr1->GetV3();
  simcYield = tr1->GetV4();
  evts = tr2->GetV1();
  q2 = tr2->GetV4();
  
  Double_t yieldRel[ndata1], hyieldRel[ndata1], pyieldRel[ndata1], unceryield[ndata1], hyield[ndata1], pyield[ndata1];
  
  cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << "yield-> ";
  
  for(Int_t i=0;i<11;i++){
  	hyield[i] = yield[i];
  	pyield[i] = yield[11+i];
  	hyieldRel[i] = hyield[i]/simcYield[i];
   	pyieldRel[i] = pyield[i]/simcYield[11+i];
  	  	
  	cout << hyield[i] << " ";
  	cout << pyield[i] << " ";
  }
  
  cout << "\n\nrelative yield-> ";
  
  for(Int_t i=0;i<ndata1;i++){
  	yieldRel[i] = yield[i]/simcYield[i];
 
   	cout << yieldRel[i] << " ";
  }
  cout << "\n\nuncertainty-> ";
  for(Int_t i=0;i<ndata1;i++){
  	unceryield[i] = TMath::Sqrt(evts[i])/evts[i];
  	
  	
  	cout << unceryield[i] << " ";
  }
  
  cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

  TCanvas *c0 = new TCanvas("c0","Yield Plots",600, 400);
  c0->SetLogy();
  
  //////////////////////////////////////////////
  
  TGraphErrors *gr1 = new TGraphErrors(ndata1,theta,yield,0,unceryield);
  gr1->SetTitle("Yield vs Theta;Theta;Yield");
  gr1->SetMarkerColor(2);
  gr1->SetMarkerStyle(20);
  gr1->Draw("AP");
  
  TGraphErrors *gr1a = new TGraphErrors(12,theta,hyield,0,unceryield);
  gr1a->SetMarkerColor(4);
  gr1a->SetMarkerStyle(20);
  gr1a->Draw("P");
  
  TLegend *leg1 = new TLegend(.75,.75,.89,.89);
  leg1->AddEntry(gr1a, "HMS yield", "lep");
  leg1->AddEntry(gr1, "SHMS yield", "lep");
  leg1->SetTextSize(0.025);
  leg1->Draw("SAME");

  c0->Print(outputpdf + "(");
  c0->Print("OUTPUT/" + foutname + "_theta.png");
  
  //////////////////////////////////////////////
  
  TGraphErrors *gr2 = new TGraphErrors(ndata1,momentum,yield,0,unceryield);
  gr2->SetTitle("Yield vs Momentum;Momentum;Yield");
  gr2->SetMarkerColor(2);
  gr2->SetMarkerStyle(20);
  gr2->Draw("AP");
  
  TGraphErrors *gr2a = new TGraphErrors(12,momentum,hyield,0,unceryield);
  gr2a->SetMarkerColor(4);
  gr2a->SetMarkerStyle(20);
  gr2a->Draw("P");
  
  TLegend *leg2 = new TLegend(.75,.75,.89,.89);
  leg2->AddEntry(gr2a, "HMS yield", "lep");
  leg2->AddEntry(gr2, "SHMS yield", "lep");
  leg2->SetTextSize(0.025);
  //leg2->Draw("SAME");

  c0->Print(outputpdf);
  c0->Print("OUTPUT/" + foutname + "_momentum.png");
  
  //////////////////////////////////////////////

  TGraphErrors *gr3 = new TGraphErrors(ndata1,q2,yield,0,unceryield);
  gr3->SetTitle("Yield vs Q^2;Q^2;Yield");
  gr3->SetMarkerColor(2);
  gr3->SetMarkerStyle(20);
  gr3->Draw("AP");
  
  TGraphErrors *gr3a = new TGraphErrors(12,q2,hyield,0,unceryield);
  gr3a->SetMarkerColor(4);
  gr3a->SetMarkerStyle(20);
  gr3a->Draw("P");
  
  TLegend *leg3 = new TLegend(.75,.75,.89,.89);
  leg3->AddEntry(gr2a, "HMS yield", "lep");
  leg3->AddEntry(gr2, "SHMS yield", "lep");
  leg3->SetTextSize(0.025);
  //leg3->Draw("SAME");
  
  c0->Print(outputpdf);
  c0->Print("OUTPUT/" + foutname + "_q2.png");
  
  //////////////////////////////////////////////
  
  TCanvas *c1 = new TCanvas("c1","Relative Yield Plots",600, 400);
  //c1->SetLogy();
   
  //////////////////////////////////////////////
  
  TGraph *gr4 = new TGraph(11,theta,yieldRel);
  //TGraph *gr4 = new TGraph(ndata1,theta,yieldRel);
  gr4->SetTitle("Relative Yield vs Theta;Theta;R = Yield_Data/Yield_SIMC");
  gr4->SetMarkerColor(4);
  gr4->SetMarkerStyle(20);
  gr4->Draw("AP");
  
  Double_t xmin4 = gr4->GetXaxis()->GetXmin();
  Double_t xmax4 = gr4->GetXaxis()->GetXmax();
  /*
  TGraph *gr4a = new TGraph(12,theta,hyieldRel);
  gr4a->SetMarkerColor(4);
  gr4a->SetMarkerStyle(20);
  gr4a->Draw("P");
  
  TLegend *leg4 = new TLegend(.75,.75,.89,.89);
  leg4->AddEntry(gr2a, "HMS yield", "lep");
  leg4->AddEntry(gr2, "SHMS yield", "lep");
  leg4->SetTextSize(0.025);
  //leg4->Draw("SAME");
  */
  
  TLine *l4 = new TLine(xmin4,1.,xmax4,1.);
  l4->SetLineColor(kRed);
  l4->Draw("lsame");
  
  c1->Print(outputpdf);
  c1->Print("OUTPUT/" + foutname + "_rel_theta.png");
  
  //////////////////////////////////////////////
  
  TGraph *gr5 = new TGraph(11,momentum,yieldRel);
  //TGraph *gr5 = new TGraph(ndata1,momentum,yieldRel);
  gr5->SetTitle("Relative Yield vs Momentum;Momentum;R = Yield_Data/Yield_SIMC");
  gr5->SetMarkerColor(4);
  gr5->SetMarkerStyle(20);
  gr5->Draw("AP");
  
  Double_t xmin5 = gr5->GetXaxis()->GetXmin();
  Double_t xmax5 = gr5->GetXaxis()->GetXmax();
  
  /*
  TGraph *gr5a = new TGraph(12,momentum,hyieldRel);
  gr5a->SetMarkerColor(4);
  gr5a->SetMarkerStyle(20);
  gr5a->Draw("P");
  
  TLegend *leg5 = new TLegend(.75,.75,.89,.89);
  leg5->AddEntry(gr2a, "HMS yield", "lep");
  leg5->AddEntry(gr2, "SHMS yield", "lep");
  leg5->SetTextSize(0.025);
  //leg4->Draw("SAME");
  */
  
  TLine *l5 = new TLine(xmin5,1.,xmax5,1.);
  l5->SetLineColor(kRed);
  l5->Draw("lsame");
  
  c1->Print(outputpdf);
  c1->Print("OUTPUT/" + foutname + "_rel_momentum.png");
  
  //////////////////////////////////////////////
  
  TGraph *gr6 = new TGraph(11,q2,yieldRel);
  //TGraph *gr6 = new TGraph(ndata1,q2,yieldRel);
  gr6->SetTitle("Relative Yield vs Q^2;Q^2;R = Yield_Data/Yield_SIMC");
  gr6->SetMarkerColor(4);
  gr6->SetMarkerStyle(20);
  gr6->Draw("AP");
  
  Double_t xmin6 = gr6->GetXaxis()->GetXmin();
  Double_t xmax6 = gr6->GetXaxis()->GetXmax();
  
  /*
  TGraph *gr6a = new TGraph(12,q2,hyieldRel);
  gr6a->SetMarkerColor(4);
  gr6a->SetMarkerStyle(20);
  gr6a->Draw("P");
  
  TLegend *leg6 = new TLegend(.75,.75,.89,.89);
  leg6->AddEntry(gr2a, "HMS yield", "lep");
  leg6->AddEntry(gr2, "SHMS yield", "lep");
  leg6->SetTextSize(0.025);
  //leg4->Draw("SAME");
  */
  
  TLine *l6 = new TLine(xmin6,1.,xmax6,1.);
  l6->SetLineColor(kRed);
  l6->Draw("lsame");
  
  c1->Print(outputpdf + ")");
  c1->Print("OUTPUT/" + foutname + "_rel_q2.png");
  


  return;

}
