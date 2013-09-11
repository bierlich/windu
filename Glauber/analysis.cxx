#include <iostream>
#include <vector>
#include <sys/wait.h>
#include "TCanvas.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TFileMerger.h"
#include "TList.h"
#include "HIParticle.h"
#include "HIEvent.h"
#include "HIInventory.h"
#include "HIAnalysis.h"
#include "styleset.h"

void makehistos(string runs,vector<double> qc);

int main(int argc=0, char *argv[]=0){
    	if(argc==1){
		cout << "NO ARGUMENT SUPPLIED!" << endl;
		return 1;
	}
	vector<string> process;
	for(int i=1;i<argc;i++){
		process.push_back(argv[i]);
	} 
	int number_of_processes = process.size();
	int pid[number_of_processes];
	for(int i=0;i<number_of_processes;i++){ //start processes loop
		 pid[i] = fork();
		 if(pid[i]==0){ //if we are a child
		 	HIAnalysis ha(process[i]);
		 	ha.EventLoop();
		 	function<bool (HIParticle*)> mastercut = [&](HIParticle *p){return (abs(p->eta)<1.0 && p->pT>0.5 && p->pT<12.0);};
		 	ha.SetMasterCut(mastercut);
		 	ha.DoRoofit(false,1);
		 	vector<vector<double>> cent = {{0.00,1.00}};
		 	vector<string> names = {"protons","pions"};
		 	vector<function<bool (HIParticle*)>> cut = {
		 						[&](HIParticle *p){return (p->pid==2212||p->pid==-2212);},
		 						[&](HIParticle *p){return (p->pid==211||p->pid==-211);}};
			ha.MultipleParticleLoops(names,cut,cent);

		 	return 0;
		 }
		 else if(pid[i]<0){
		 	cerr << "ERROR! FAILED TO FORK!" << endl;
		 	return 1;
		 }
	}
	for (int i=0; i<number_of_processes;i++){
    	int status;
    	while(waitpid(pid[i], &status, 0)==-1){
    	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0){
        cout << "Process " << i << " (name " << process[i] << " pid " << pid[i] << ") failed" << endl;
    		}
    	}
	}
	if(number_of_processes>0){
		TFile * f = new TFile("histograms.root","UPDATE");
		f->Close();
		TFileMerger * fm = new TFileMerger();
 		fm->OutputFile("histograms.root");
    	for(int i=0;i<number_of_processes;i++){
    		fm->AddFile((process[i] + ".root").c_str());
    		}
    	fm->Merge();
    }
    
    return 0;
}