using namespace std;

void read_file(){
    
    TFile *fin = new TFile("../files/icarus_out_tree.root", "READ");
    
    TTree *icarus_tree = (TTree*)fin->Get("input_tree/infotree_slice");
    TTree *icarus_tree_tracks = (TTree*)fin->Get("input_tree/infotree_tracks");
    
    
    int run[2], subrun[2],evt[2],slice[2];
    double reco_ntracks;
    
    icarus_tree->SetBranchAddress("Run",&run[0]); icarus_tree_tracks->SetBranchAddress("Run",&run[1]);
    icarus_tree->SetBranchAddress("Subrun",&subrun[0]); icarus_tree_tracks->SetBranchAddress("Subrun",&subrun[1]);
    icarus_tree->SetBranchAddress("Evt",&evt[0]); icarus_tree_tracks->SetBranchAddress("Evt",&evt[1]);
    icarus_tree->SetBranchAddress("Slice",&slice[0]); icarus_tree_tracks->SetBranchAddress("Slice",&slice[1]);
    icarus_tree->SetBranchAddress("NTracks",&reco_ntracks);
    
    std::tuple<int,int,int,int> slice_tuple, track_multivar_tuple;
   
    int track_index_counter = 0;
    
    map<int,vector<int>> slice_track_index;
    
    cout << Form("Found %i slices", (int)icarus_tree->GetEntries()) << endl;
    int n_entries = (int)icarus_tree->GetEntries();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    for(int i = 0; i < icarus_tree->GetEntries(); i++){ //icarus_tree->GetEntries()
        
        if(i == n_entries-1)break; //weird things happen with the last entry
        
        if(i%10000 == 0) cout << "Processing slice " << i << endl;
        
        icarus_tree->GetEntry(i);
        slice_tuple = make_tuple(run[0],subrun[0], evt[0], slice[0]);
       
        std::vector<int> track_idx;
        bool equal = true;
        
        while(equal){
            icarus_tree_tracks->GetEntry(track_index_counter);
            
            track_multivar_tuple = make_tuple(run[1],subrun[1], evt[1], slice[1]);
            
            if(slice_tuple == track_multivar_tuple){
                track_idx.push_back(track_index_counter);
                track_index_counter++;}
            else equal = false;
        }
        if(!((int)reco_ntracks == (int)track_idx.size()))break; //checks consistency
        
        slice_track_index[i] = track_idx;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    double true_neutrino_flavour, true_nuetrino_current_type, true_q2, true_interaction_type, true_topology, true_energy_neutrino, true_vertex_x, true_vertex_y, true_vertex_z;
    double reco_topology, reco_vertex_x, reco_vertex_y, reco_vertex_z;
    
    icarus_tree->SetBranchAddress("TrueNeutrinoFlavour",&true_neutrino_flavour);
    icarus_tree->SetBranchAddress("NeutrinoCurrentType",&true_nuetrino_current_type);
    icarus_tree->SetBranchAddress("TrueQ2",&true_q2);
    icarus_tree->SetBranchAddress("TrueInteractionType",&true_interaction_type);
    icarus_tree->SetBranchAddress("TrueTopology",&true_topology);
    icarus_tree->SetBranchAddress("TrueVertexPositionX",&true_vertex_x);
    icarus_tree->SetBranchAddress("TrueVertexPositionY",&true_vertex_y);
    icarus_tree->SetBranchAddress("TrueVertexPositionZ",&true_vertex_z);
    icarus_tree->SetBranchAddress("TrueEnergyNeutrino",&true_energy_neutrino);
    
    
    icarus_tree->SetBranchAddress("RecoTopology",&reco_topology);
    icarus_tree->SetBranchAddress("RecoVertexX",&reco_vertex_x);
    icarus_tree->SetBranchAddress("RecoVertexY",&reco_vertex_y);
    icarus_tree->SetBranchAddress("RecoVertexZ",&reco_vertex_z);
   
    
    
    double true_track_pdg, true_track_momenta_x, true_track_momenta_y, true_track_momenta_z, true_track_energy, true_track_start_pos_x, true_track_start_pos_y, true_track_start_pos_z, true_track_end_pos_x, true_track_end_pos_y, true_track_end_pos_z;
    
    double reco_track_score, reco_track_pdg, reco_track_cosT, reco_track_phi, reco_track_momenta, reco_track_start_pos_x, reco_track_start_pos_y, reco_track_start_pos_z, reco_track_end_pos_x, reco_track_end_pos_y, reco_track_end_pos_z;
    
    
    icarus_tree_tracks->SetBranchAddress("TrackTruePdg", &true_track_pdg);
    icarus_tree_tracks->SetBranchAddress("TrackTrueMomentaX", &true_track_momenta_x);
    icarus_tree_tracks->SetBranchAddress("TrackTrueMomentaY", &true_track_momenta_y);
    icarus_tree_tracks->SetBranchAddress("TrackTrueMomentaZ", &true_track_momenta_z);
    icarus_tree_tracks->SetBranchAddress("TrackTrueE", &true_track_energy);
    icarus_tree_tracks->SetBranchAddress("TrackTrueStartPosX", &true_track_start_pos_x);
    icarus_tree_tracks->SetBranchAddress("TrackTrueStartPosY", &true_track_start_pos_y);
    icarus_tree_tracks->SetBranchAddress("TrackTrueStartPosZ", &true_track_start_pos_z);
    icarus_tree_tracks->SetBranchAddress("TrackTrueEndPosX", &true_track_end_pos_x);
    icarus_tree_tracks->SetBranchAddress("TrackTrueEndPosY", &true_track_end_pos_y);
    icarus_tree_tracks->SetBranchAddress("TrackTrueEndPosZ", &true_track_end_pos_z);

    icarus_tree_tracks->SetBranchAddress("TrackScore", &reco_track_score);
    icarus_tree_tracks->SetBranchAddress("TrackSelPdg", &reco_track_pdg);
    icarus_tree_tracks->SetBranchAddress("TrackRecoCosZ", &reco_track_cosT);
    icarus_tree_tracks->SetBranchAddress("TrackRecoPhi", &reco_track_phi);
    icarus_tree_tracks->SetBranchAddress("TrackRecoMomenta", &reco_track_momenta);
    icarus_tree_tracks->SetBranchAddress("TrackStartPosX", &reco_track_start_pos_x);
    icarus_tree_tracks->SetBranchAddress("TrackStartPosY", &reco_track_start_pos_y);
    icarus_tree_tracks->SetBranchAddress("TrackStartPosZ", &reco_track_start_pos_z);
    icarus_tree_tracks->SetBranchAddress("TrackEndPosX", &reco_track_end_pos_x);
    icarus_tree_tracks->SetBranchAddress("TrackEndPosY", &reco_track_end_pos_y);
    icarus_tree_tracks->SetBranchAddress("TrackEndPosZ", &reco_track_end_pos_z);
    

    
    TH1D *hist = new TH1D("","",50, 0,3);
    TH1D *hTrueEnu = new TH1D("hTrueEnu","",50, 0,3);
    TGraph *pos = new TGraph(int(icarus_tree_tracks->GetEntries()));
    TH1D *hTrueEnu_0pi = new TH1D("hTrueEnu_0pi","",50, 0,3);
    TH1D *hTrueEnu_Npi = new TH1D("hTrueEnu_Npi","",50, 0,3);
  
    /*
    for(int slc_id =0; slc_id < (int)slice_track_index.size(); slc_id++){
        
        icarus_tree->GetEntry(slc_id);
      //  hist->Fill(true_energy_neutrino);
    }
    
    
    for(int trk_id =0; trk_id < (int)icarus_tree_tracks->GetEntries(); trk_id++){
        icarus_tree_tracks->GetEntry(trk_id);
        hist->Fill(reco_track_score);
        //pos->SetPoint(trk_id, trk_id, reco_track_momenta);
    }
                         
    */
    for(int slc = 0; slc < (int)slice_track_index.size(); slc++){
      icarus_tree->GetEntry(slc);
      hTrueEnu->Fill(true_energy_neutrino);
      int npi = 0;
      

      
   
     

      
        for(int trkid : slice_track_index[slc]){
            icarus_tree_tracks->GetEntry(trkid);
            if(reco_track_pdg == 13)hist->Fill(reco_track_momenta);
	    if(abs(true_track_pdg) == 211)npi++;


        }

	if (npi == 0) hTrueEnu_0pi->Fill(true_energy_neutrino);
	if (npi >  0) hTrueEnu_Npi->Fill(true_energy_neutrino);
    }
    
      TFile *fout = new TFile("../files/icarus_ana_out.root", "recreate");
    TCanvas *c1 = new TCanvas("","",800,600);
   // pos->Draw("AP");
    hist->Draw();

     TCanvas *c2 = new TCanvas("","",800,600);
     hTrueEnu->Draw();


     
     fout->cd();
      hTrueEnu->Write();
      hTrueEnu_0pi->Write();
      hTrueEnu_Npi->Write();
      fout->Close();
      fin->Close();
}
