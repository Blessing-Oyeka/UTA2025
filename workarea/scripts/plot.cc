using namespace std;

// Function to call a 2D histogram into a 1D: energy vs mode of Y (Reco - True)
TH1D* GetModeProfile(TH2D* h2, const char* nameofhist) {
    if (!h2) return nullptr;

    const TAxis* xaxis = h2->GetXaxis();
    const TAxis* yaxis = h2->GetYaxis();
    int nbinsX = xaxis->GetNbins();

    // Output histogram: same binning in X, Y value = mode from projection
    TH1D* hMode = new TH1D(nameofhist, " ;Reconstructed Neutrino Energy [GeV];Most Probable((True - Reco)/True) [GeV]",
                           nbinsX, xaxis->GetXmin(), xaxis->GetXmax());

    for (int ix = 1; ix <= nbinsX; ++ix) {
        // Project Y axis at given X bin
        TH1D* hProjY = h2->ProjectionY("_py", ix, ix);
        if (hProjY->GetEntries() == 0) {
            delete hProjY;
            continue;
        }

        int imax = hProjY->GetMaximumBin();
        double modeY = hProjY->GetBinCenter(imax);
        hMode->SetBinContent(ix, modeY);

        delete hProjY;
    }

    return hMode;
}

void applyCommonCanvasSettings() {
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);
}


void plot(){
  ////////USE get command, use drawhist    
  TFile *fin = new TFile("../files/icarus_ana_out.root", "READ");

    TH1D *hTrueEnu = (TH1D*)fin->Get("hTrueEnu");
    TH1D *hRecoEnuInc = (TH1D*)fin->Get("hRecoEnuInc");
    TH1D *hRecoEnuT2k = (TH1D*)fin->Get("hRecoEnuT2k");
    
    TH1D *hTrueEnu_0pi = (TH1D*)fin->Get("hTrueEnu_0pi");
    TH1D *hRecoEnuInc_0pi = (TH1D*)fin->Get("hRecoEnuInc_0pi");
    TH1D *hRecoEnuT2k_0pi = (TH1D*)fin->Get("hRecoEnuT2k_0pi");

    TH1D *hTrueEnu_Npi = (TH1D*)fin->Get("hTrueEnu_Npi");
    TH1D *hRecoEnuInc_npi = (TH1D*)fin->Get("hRecoEnuInc_npi");
    TH1D *hRecoEnuT2k_npi = (TH1D*)fin->Get("hRecoEnuT2k_npi");

    TH1D *hRecoEnuInc_signal = (TH1D*)fin->Get("hRecoEnuInc_signal");
    TH1D *hRecoEnuT2k_IncSignal = (TH1D*)fin->Get("hRecoEnuT2k_IncSignal");

    TH1D *hResEnu_vis = (TH1D*)fin->Get("hResEnu_vis");
    TH1D *hResEnu_t2kqe = (TH1D*)fin->Get("hResEnu_t2kqe");

    TH1D *hResEnu_Vis_signal = (TH1D*)fin->Get("hResEnu_Vis_signal");
    TH1D *hResEnu_t2kqe_signal = (TH1D*)fin->Get("hResEnu_t2kqe_signal");

    TH1D *hResEnu0pi_vis = (TH1D*)fin->Get("hResEnu0pi_vis");
    TH1D *hResEnu0pi_t2kqe = (TH1D*)fin->Get("hResEnu0pi_t2kqe");
    TH1D *hResEnuNpi_vis = (TH1D*)fin->Get("hResEnuNpi_vis");
    TH1D *hResEnuNpi_t2kqe = (TH1D*)fin->Get("hResEnuNpi_t2kqe");
    
    ///These are the signal topologies
    TH2D *hResEnu0pi_viSig = (TH2D*)fin->Get("hResEnu0pi_viSig");
    TH2D *hResEnuNpi_viSig = (TH2D*)fin->Get("hResEnuNpi_viSig");
    TH2D *hResEnu0pi_t2kSig = (TH2D*)fin->Get("hResEnu0pi_t2kSig");
    TH2D *hResEnuNpi_t2kSig = (TH2D*)fin->Get("hResEnuNpi_t2kSig");

    TH2D *hResEnuInc_2Dsignal = (TH2D*)fin->Get("hResEnuInc_2Dsignal");
    TH2D *hResEnuT2k_2Dsignal = (TH2D*)fin->Get("hResEnuT2k_2Dsignal");

    TH1D *hTrueEnu_Np0pi = (TH1D*)fin->Get("hTrueEnu_Np0pi");
    TH1D *hResEnuInc_Np0pi_S = (TH1D*)fin->Get("hResEnuInc_Np0pi_S");
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TH1D *hResEnuNp0pi_argo =  (TH1D*)fin->Get("hResEnuNp0pi_argo");
    TH1D *hResEnuNp0pi_argo_sig = (TH1D*)fin->Get("hResEnuNp0pi_argo_sig");

    TH1D *hRecoEnuNp0pi_argo =  (TH1D*)fin->Get("hRecoEnuNp0pi_argo");
    TH1D *hRecoEnuNp0pi_argo_sig = (TH1D*)fin->Get("hRecoEnuNp0pi_argo_sig");

    TH2D *hResEnuNp0pi_argo_sig2D = (TH2D*)fin->Get("hResEnuNp0pi_argo_sig2D");

    TH2D *hRecoEnuInc_Np0pi = (TH2D*)fin->Get("hRecoEnuInc_Np0pi");

    TH2D *hResEnuInc_Np0pi_S2D = (TH2D*)fin->Get("hResEnuInc_Np0pi_S2D");
    
    
    //////////////////////////////////////////////////////////////////////////////////////////////tgraps
    TVectorD *vResEnu_Vis_signal_T =  (TVectorD*)fin->Get("vResEnu_Vis_signal_T");
    // for(int i = 0 ; i <vResEnu_Vis_signal_T->GetNrows();++i)std::cout<<(*vResEnu_Vis_signal_T)[i]<<std::endl; 

    TVectorD *vResEnu_t2kqe_signal_T =  (TVectorD*)fin->Get("vResEnu_t2kqe_signal_T");
    //for(int i = 0 ; i <vResEnu_t2kqe_signal_T->GetNrows();++i)std::cout<<(*vResEnu_t2kqe_signal_T)[i]<<std::endl;

    TVectorD *vRecoEnu_Vis_signal_T =  (TVectorD*)fin->Get("vRecoEnu_Vis_signal_T");
    //for(int i = 0 ; i <vRecoEnu_Vis_signal_T->GetNrows();++i)std::cout<<(*vRecoEnu_Vis_signal_T)[i]<<std::endl;

    TVectorD *vRecoEnu_t2kqe_signal_T =  (TVectorD*)fin->Get("vRecoEnu_t2kqe_signal_T");
    // for(int i = 0 ; i <vRecoEnu_t2kqe_signal_T->GetNrows();++i)std::cout<<(*vRecoEnu_t2kqe_signal_T)[i]<<std::endl;

    TVectorD *vRecoEnuNp0pi_argo_sig_T =  (TVectorD*)fin->Get("vRecoEnuNp0pi_argo_sig_T");
    // for(int i = 0 ; i <vRecoEnuNp0pi_argo_sig_T->GetNrows();++i)std::cout<<(*vRecoEnuNp0pi_argo_sig_T)[i]<<std::endl;

    TVectorD *vResEnuNp0pi_argo_sig_T =  (TVectorD*)fin->Get("vResEnuNp0pi_argo_sig_T");
    // for(int i = 0 ; i <vResEnuNp0pi_argo_sig_T->GetNrows();++i)std::cout<<(*vResEnuNp0pi_argo_sig_T)[i]<<std::endl;

    TVectorD *vResEnuInc_Np0pi_S_T =  (TVectorD*)fin->Get("vResEnuInc_Np0pi_S_T");
    // for(int i = 0 ; i <vResEnuInc_Np0pi_S_T->GetNrows();++i)std::cout<<(*vResEnuInc_Np0pi_S_T)[i]<<std::endl;
       



    

    //////////////////////////////////////////////////////////////CANVAS
    TCanvas* c1 = new TCanvas("c1", "Inclusive", 800, 600);
    hTrueEnu->SetLineColor(kGray);
    /*hTrueEnu->SetFillColor(kGray);
    hTrueEnu->SetLineWidth(2);*/
    hTrueEnu->SetFillColorAlpha(kGray, 0.35);
    
    hRecoEnuInc->SetLineColor(kRed);
    hRecoEnuInc->SetLineWidth(2);
    hRecoEnuT2k->SetLineColor(kBlack);
    hRecoEnuT2k->SetLineWidth(2);


    hRecoEnuT2k->SetStats(0);
    hRecoEnuT2k->GetXaxis()->SetTitle("Neutrino Energy (GeV)");
    hRecoEnuT2k->GetYaxis()->SetTitle("Entries");
    hRecoEnuT2k->Draw("Hist");
    hRecoEnuInc->Draw("Hist same");
    hTrueEnu->Draw("same");

    TLegend *l1 = new TLegend(0.65, 0.75, 0.88, 0.88);
    l1->AddEntry(hTrueEnu, "True E_{#nu}", "l");
    l1->AddEntry(hRecoEnuInc, "Reco Vis. E_{#nu}", "l");
    l1->AddEntry(hRecoEnuT2k, "Reco T2K QE E_{#nu}", "l");

    l1->Draw();
   
    
    c1->SaveAs("../plots/test.pdf");
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    TCanvas* c2 = new TCanvas("c2", "", 800, 600);
    hResEnu_vis->SetLineColor(kBlue);
    hResEnu_vis->SetLineWidth(2);
    hResEnu_t2kqe->SetLineColor(kRed);
    hResEnu_t2kqe->SetLineWidth(2);


    hResEnu_vis->SetStats(0);
    hResEnu_vis->GetXaxis()->SetTitle("E_{#nu} ((True - Reco) / True)");
    hResEnu_vis->GetXaxis()->SetTitleOffset(1.2);   
    // hResEnu_vis->GetXaxis()->SetTitle("Neutrino Energy");
    hResEnu_vis->GetYaxis()->SetTitle("Entries");
    
    hResEnu_vis->Draw("Hist");
    hResEnu_t2kqe->Draw("Hist same");

    TLegend *l2 = new TLegend(0.65, 0.75, 0.88, 0.88);
    l2->AddEntry(hResEnu_vis, "Res Vis E_{#nu}", "l");
    l2->AddEntry(hResEnu_t2kqe, "Res T2KQE E_{#nu}", "l");

    l2->Draw();

    c2->SaveAs("../plots/Res.pdf");

    /////////////////////////////////////////////////////////////////////// 

     TCanvas* c3 = new TCanvas("c3", "Inclusive", 800, 600);
     hTrueEnu->SetLineColor(kGray);
     /*hTrueEnu->SetFillColor(kGray);
     hTrueEnu->SetLineWidth(2);*/
     hTrueEnu->SetFillColorAlpha(kGray, 0.35);
    
     hRecoEnuInc_signal->SetLineColor(kRed);
     hRecoEnuInc_signal->SetLineWidth(2);
     hRecoEnuT2k_IncSignal->SetLineColor(kBlack);
     hRecoEnuT2k_IncSignal->SetLineWidth(2);

     hRecoEnuInc_signal->SetStats(0);
     hRecoEnuInc_signal->GetXaxis()->SetTitle("Neutrino Energy (GeV)");
     hRecoEnuInc_signal->GetYaxis()->SetTitle("Entries");
     hRecoEnuInc_signal->Draw("Hist");
     hRecoEnuT2k_IncSignal->Draw("Hist same");
     hTrueEnu->Draw("same");
    

     TLegend *l3 = new TLegend(0.65, 0.75, 0.88, 0.88);
     l3->AddEntry(hRecoEnuInc_signal, "Reco Vis. E_{#nu}", "l");
     l3->AddEntry(hRecoEnuT2k_IncSignal, "Reco T2K QE E_{#nu}", "l");
     l3->AddEntry(hTrueEnu, "True E_{#nu}", "l");
     l3->Draw();
   
    
     c3->SaveAs("../plots/RecoEnuInc.pdf");
     ////////////////////////////////////////////////////////////////////////


     TCanvas* c4 = new TCanvas("c4", "", 800, 600);
     hResEnu_Vis_signal->SetLineColor(kBlue);
     hResEnu_Vis_signal->SetLineWidth(2);
     hResEnu_t2kqe_signal->SetLineColor(kRed);
     hResEnu_t2kqe_signal->SetLineWidth(2);


     hResEnu_Vis_signal->SetStats(0);                  
     hResEnu_Vis_signal->GetXaxis()->SetTitle("E_{#nu} ((True - Reco) / True)");
     hResEnu_Vis_signal->GetXaxis()->SetTitleOffset(1.2);   
    // hResEnu_vis->GetXaxis()->SetTitle("Neutrino Energy");
     hResEnu_Vis_signal->GetYaxis()->SetTitle("Entries");
    
     hResEnu_Vis_signal->Draw("Hist");
     hResEnu_t2kqe_signal->Draw("Hist same");

     TLegend *l4 = new TLegend(0.63, 0.75, 0.88, 0.88);
     l4->AddEntry(hResEnu_Vis_signal, "Res Vis_S E_{#nu}", "l");
     l4->AddEntry(hResEnu_t2kqe_signal, "Res T2KQE_S E_{#nu}", "l");

     l4->Draw();
     
     c4->SaveAs("../plots/Res_signal.pdf");
     
     ///////////////////////////////////////////////////////////////////////////////
    
     TCanvas* c5 = new TCanvas("c5", "", 800, 600);
     hResEnu0pi_vis->SetLineColor(kBlue);
     hResEnu0pi_vis->SetLineWidth(2);
     hResEnuNpi_vis->SetLineColor(kRed);
     hResEnuNpi_vis->SetLineWidth(2);
     hResEnu0pi_t2kqe->SetLineColor(kBlack);
     hResEnu0pi_t2kqe->SetLineWidth(2);
     hResEnuNpi_t2kqe->SetLineColor(kYellow);
     hResEnuNpi_t2kqe->SetLineWidth(2); 

     hResEnu0pi_vis->SetStats(0);
     hResEnu0pi_vis->GetXaxis()->SetTitle("E_{#nu} ((True - Reco) / True)");
     hResEnu0pi_vis->GetXaxis()->SetTitleOffset(1.2);   
    // hResEnu_vis->GetXaxis()->SetTitle("Neutrino Energy");
     hResEnu0pi_vis->GetYaxis()->SetTitle("Entries");
    
     hResEnu0pi_vis->Draw("Hist");
     hResEnuNpi_vis->Draw("Hist same");
     hResEnu0pi_t2kqe->Draw("same");
     hResEnuNpi_t2kqe->Draw("same");

   

     TLegend *l5 = new TLegend(0.63, 0.75, 0.88, 0.88);
     l5->AddEntry(hResEnu0pi_vis, "Res Vis_0pi E_{#nu}", "l");
     l5->AddEntry(hResEnuNpi_vis, "Res Vis_Npi E_{#nu}", "l");  
     l5->AddEntry(hResEnu0pi_t2kqe, "Res T2KQE_0pi E_{#nu}", "l");
     l5->AddEntry(hResEnuNpi_t2kqe, "Res T2KQE_Npi E_{#nu}", "l");

     l5->Draw();
     
     c5->SaveAs("../plots/Res_0piNpi.pdf");
     ////////////////////////////////////////////////////////////////////////////////////////////////
     //////////////////////////////////////////////////////2D SIGNAL TOPOLOGIES INCLUSIVE
     TH1D* hResIncVis = GetModeProfile(hResEnuInc_2Dsignal, "hResIncVis");
     hResIncVis->SetLineColor(kRed);
     hResIncVis->SetLineWidth(2);

     gStyle->SetOptStat(0000);
     
     // Draw results///////
     TCanvas* c6 = new TCanvas();
     gStyle->SetPalette(kInvertedDarkBodyRadiator);
     hResEnuInc_2Dsignal->GetYaxis()->SetTitle("E_{#nu} ((True - Reco) / True)");
     hResEnuInc_2Dsignal->GetXaxis()->SetTitle("Reconstructed Neutrino Energy");
     
     hResEnuInc_2Dsignal->Draw("colz");
     c6->SaveAs("../plots/ResIncVis2D.pdf");
    
     TH1D* hResIncT2K = GetModeProfile(hResEnuT2k_2Dsignal, "hResIncT2K");
     hResIncT2K->SetLineColor(kBlue);
     hResIncT2K->SetLineWidth(2);

     gStyle->SetOptStat(0000);
     
     // Draw results///////
     TCanvas* c7 = new TCanvas();
     gStyle->SetPalette(kBird);
     hResEnuT2k_2Dsignal->GetYaxis()->SetTitle("E_{#nu} ((True - Reco) / True)");
     hResEnuT2k_2Dsignal->GetXaxis()->SetTitle("Reconstructed Neutrino Energy");
     
     hResEnuT2k_2Dsignal->Draw("colz");
     c7->SaveAs("../plots/ResIncT2K2D.pdf");

      //////////////////////////////Extracting 2D to 1D
     TCanvas* c8 = new TCanvas();
     hResIncVis->Draw("hist");
     hResIncT2K->Draw("hist same");//////new addition

     TLegend *l8 = new TLegend(0.63, 0.75, 0.88, 0.88);
     l8->AddEntry(hResIncVis, "Mode (Vis. Res)", "l");
     l8->AddEntry(hResIncT2K, "Mode (T2KQE Res)", "l");
     l8->Draw();
   
     c8->SaveAs("../plots/ResIncVis.T2K.1D.pdf");

     
     ///////////////////////////////////////////2D SIGNAL TOPOLOGIES FOR 0pi AND Npi
     //////////////Visible Approach 0pi
     TH1D* hResEnu0pi_viS = GetModeProfile(hResEnu0pi_viSig, "hResEnu0pi_viS");
     hResEnu0pi_viS->SetLineColor(kRed);
     hResEnu0pi_viS->SetLineWidth(2);
     
     gStyle->SetOptStat(0000);
    
     TCanvas* c9 = new TCanvas();
     gStyle->SetPalette(kInvertedDarkBodyRadiator);
     hResEnu0pi_viSig->GetYaxis()->SetTitle("E_{#nu} ((True - Reco) / True)");
     hResEnu0pi_viSig->GetXaxis()->SetTitle("Reconstructed Neutrino Energy");
     
     hResEnu0pi_viSig->Draw("colz");   
     c9->SaveAs("../plots/ResSig0pivis.pdf");
     
     //////////T2K Approach 0pi
     TH1D* hResEnu0pi_t2kS = GetModeProfile(hResEnu0pi_t2kSig, "hResEnu0pi_t2kS");
     hResEnu0pi_t2kS->SetLineColor(kBlue);
     hResEnu0pi_t2kS->SetLineWidth(2);

     gStyle->SetOptStat(0000);

     TCanvas* c10 = new TCanvas();
     gStyle->SetPalette(kBird);
     hResEnu0pi_t2kSig->GetYaxis()->SetTitle("E_{#nu} ((True - Reco) / True)");
     hResEnu0pi_t2kSig->GetXaxis()->SetTitle("Reconstructed Neutrino Energy");

     hResEnu0pi_t2kSig->Draw("colz");
     c10->SaveAs("../plots/ResSig0pit2k.pdf");

     TCanvas* c11 = new TCanvas();
     hResEnu0pi_viS->Draw("hist");
     hResEnu0pi_t2kS->Draw("hist same");

     TLegend *l11 = new TLegend(0.63, 0.75, 0.88, 0.88);
     l11->AddEntry(hResEnu0pi_viS, "Mode (Vis.0pi)", "l");
     l11->AddEntry(hResEnu0pi_t2kS, "Mode (T2KQE 0pi)", "l");
     l11->Draw();
   
     c11->SaveAs("../plots/Res0piVis.T2K.1D.pdf");

     //////////////Visible Approach Npi
     TH1D* hResEnuNpi_viS = GetModeProfile(hResEnuNpi_viSig, "hResEnuNpi_viS");
     hResEnuNpi_viS->SetLineColor(kRed);
     hResEnuNpi_viS->SetLineWidth(2);
     
     gStyle->SetOptStat(0000);
    
     TCanvas* c12 = new TCanvas();
     gStyle->SetPalette(kInvertedDarkBodyRadiator);
     hResEnuNpi_viSig->GetYaxis()->SetTitle("E_{#nu} ((True - Reco) / True)");
     hResEnuNpi_viSig->GetXaxis()->SetTitle("Reconstructed Neutrino Energy");
     
     hResEnuNpi_viSig->Draw("colz");   
     c12->SaveAs("../plots/ResSigNpivis.pdf");
     
     //////////T2K Approach Npi
     TH1D* hResEnuNpi_t2kS = GetModeProfile(hResEnuNpi_t2kSig, "hResEnuNpi_t2kS");
     hResEnuNpi_t2kS->SetLineColor(kBlue);
     hResEnuNpi_t2kS->SetLineWidth(2);

     gStyle->SetOptStat(0000);

     /////////////////////////////////////////////////////////////////////
     /////////////////////////////////////////////////////////////////////
     TCanvas* c13 = new TCanvas();
     applyCommonCanvasSettings();
     gStyle->SetPalette(kBird);
     hResEnuNpi_t2kSig->GetYaxis()->SetTitle("E_{#nu} ((True - Reco) / True)");
     hResEnuNpi_t2kSig->GetXaxis()->SetTitle("Reconstructed Neutrino Energy");

     hResEnuNpi_t2kSig->Draw("colz");
     c13->SaveAs("../plots/ResSigNpit2k.pdf");

     TCanvas* c14 = new TCanvas();
     applyCommonCanvasSettings();
     hResEnuNpi_viS->Draw("hist");
     hResEnuNpi_t2kS->Draw("hist same");

     TLegend *l14 = new TLegend(0.63, 0.75, 0.88, 0.88);
     l14->AddEntry(hResEnuNpi_viS, "Mode (Vis.Npi)", "l");
     l14->AddEntry(hResEnuNpi_t2kS, "Mode (T2KQE Npi)", "l");
     l14->Draw();
   
     c14->SaveAs("../plots/ResNpiVis.T2K.1D.pdf");


     TCanvas* c15 = new TCanvas("c15", "", 800, 600);
     hResEnuInc_Np0pi_S->SetLineColor(kRed);
     hResEnuInc_Np0pi_S->SetLineWidth(2);
     hResEnuNp0pi_argo_sig->SetLineColor(kBlue);
     hResEnuNp0pi_argo_sig->SetLineWidth(2);


     hResEnuNp0pi_argo_sig->SetStats(0);                  
     hResEnuNp0pi_argo_sig->GetXaxis()->SetTitle("E_{#nu} ((True - Reco) / True)");
     hResEnuNp0pi_argo_sig->GetXaxis()->SetTitleOffset(1.2);   
     hResEnuNp0pi_argo_sig->GetYaxis()->SetTitle("Entries");
    
     hResEnuNp0pi_argo_sig->Draw("Hist");
     hResEnuInc_Np0pi_S->Draw("Hist same");

     TLegend *l15 = new TLegend(0.63, 0.75, 0.88, 0.88);
     l15->AddEntry(hResEnuNp0pi_argo_sig, "ResArgoNeuTSig E_{#nu}", "l");
     l15->AddEntry(hResEnuInc_Np0pi_S, "ResInc E_{#nu}", "l");

     l15->Draw();
     
     c15->SaveAs("../plots/ArgoVis1DRes.pdf");


     TCanvas* c16 = new TCanvas("c16", "Inclusive", 800, 600);
     hTrueEnu_Np0pi->SetLineColor(kGray);
     hTrueEnu_Np0pi->SetFillColorAlpha(kGray, 0.35);
    
     hRecoEnuInc_Np0pi->SetLineColor(kRed);
     hRecoEnuInc_Np0pi->SetLineWidth(2);
     hRecoEnuNp0pi_argo_sig->SetLineColor(kBlack);
     hRecoEnuNp0pi_argo_sig->SetLineWidth(2);

     hTrueEnu_Np0pi->SetStats(0);
     hTrueEnu_Np0pi->GetXaxis()->SetTitle("Neutrino Energy (GeV)");
     hTrueEnu_Np0pi->GetYaxis()->SetTitle("Entries");
     hTrueEnu_Np0pi->Draw("Hist");
     hRecoEnuNp0pi_argo_sig->Draw("Hist same");
     hRecoEnuInc_Np0pi->Draw("same");
    

     TLegend *l16 = new TLegend(0.65, 0.75, 0.88, 0.88);
     l16->AddEntry(hRecoEnuInc_Np0pi, "RecoEnuInc_Sig E_{#nu}", "l");
     l16->AddEntry(hRecoEnuNp0pi_argo_sig, "Reco Argo Sig E_{#nu}", "l");
     l16->AddEntry(hTrueEnu_Np0pi, "True E_{#nu}", "l");
     l16->Draw();
   
    
     c16->SaveAs("../plots/Argo1DReco.pdf");

     TH1D* hResEnuInc_Np0pi_S1D = GetModeProfile(hResEnuInc_Np0pi_S2D, "hResEnuInc_Np0pi_S1D");
     hResEnuInc_Np0pi_S1D->SetLineColor(kRed);
     hResEnuInc_Np0pi_S1D->SetLineWidth(2);
     
     gStyle->SetOptStat(0000);
    
     TCanvas* c17 = new TCanvas();
     gStyle->SetPalette(kInvertedDarkBodyRadiator);
     hResEnuInc_Np0pi_S2D->GetYaxis()->SetTitle("E_{#nu} ((True - Reco) / True)");
     hResEnuInc_Np0pi_S2D->GetXaxis()->SetTitle("Reconstructed Neutrino Energy");
     
     hResEnuInc_Np0pi_S2D->Draw("colz");   
     c17->SaveAs("../plots/ResEnuIncNp0pi.pdf");
    

     TH1D* hResEnuNp0pi_argo_signal = GetModeProfile(hResEnuNp0pi_argo_sig2D, "hResEnuNp0pi_argo_signal");
     hResEnuNp0pi_argo_signal->SetLineColor(kBlue);
     hResEnuNp0pi_argo_signal->SetLineWidth(2);

     gStyle->SetOptStat(0000);

     TCanvas* c18 = new TCanvas();
     gStyle->SetPalette(kBird);
     hResEnuNp0pi_argo_sig2D->GetYaxis()->SetTitle("E_{#nu} ((True - Reco) / True)");
     hResEnuNp0pi_argo_sig2D->GetXaxis()->SetTitle("Reconstructed Neutrino Energy");

     hResEnuNp0pi_argo_sig2D->Draw("colz");
     c18->SaveAs("../plots/hResEnuNp0pi_argoneut_2D_sig.pdf");

     TCanvas* c19 = new TCanvas();
     hResEnuInc_Np0pi_S1D->GetYaxis()->SetRangeUser(-0.7, 1.0);
     hResEnuInc_Np0pi_S1D->Draw("hist");
     hResEnuNp0pi_argo_signal->Draw("hist same");

     TLegend *l19 = new TLegend(0.63, 0.75, 0.88, 0.88);
     /* l19->SetTextSize(0.035);
	l19->SetBorderSize(0);*/
     l19->AddEntry(hResEnuNp0pi_argo_signal, "Mode (Argo Np0pi)", "l");
     l19->AddEntry(hResEnuInc_Np0pi_S1D, "Mode (EnuInc Np0pi)", "l");
     l19->Draw();
   
     c19->SaveAs("../plots/ArgovsVis.pdf");

}












/*TCanvas* c1 = new TCanvas();
    THStack* hsEnu = new THStack("","");//////remove
    hsEnu->Add(hTrueEnu_0pi);
    hsEnu->Add(hTrueEnu_Npi);
    hsEnu->Draw("hist");

 hTrueEnu_0pi->SetFillColor(kRed);
 hTrueEnu_Npi->SetFillColor(kBlue);*/
