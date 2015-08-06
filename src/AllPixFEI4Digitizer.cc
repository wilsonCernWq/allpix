/**
 *  Author:
 *    francesco.armando.di.bello@cern.ch
 *
 *  allpix Authors:
 *   John Idarraga <idarraga@cern.ch>
 *   Mathieu Benoit <benoit@lal.in2p3.fr>
 */

#include "AllPixFEI4Digitizer.hh"
#include "AllPixTrackerHit.hh"
#include "G4DigiManager.hh"
#include "G4VDigitizerModule.hh"
#include "AllPixGeoDsc.hh"

#include "TMath.h"
#include "TF1.h"
#include "TRandom.h"
#include <TH2F.h>
#include <TF1.h>
#include <TFile.h>

AllPixFEI4Digitizer::AllPixFEI4Digitizer(G4String modName, G4String hitsColName, G4String digitColName) 
: AllPixDigitizerInterface (modName) {

	// Registration of digits collection name
	collectionName.push_back(digitColName);
	m_hitsColName.push_back(hitsColName);

	// threshold
	m_digitIn.thl = 0.;

}

AllPixFEI4Digitizer::~AllPixFEI4Digitizer(){

}

void AllPixFEI4Digitizer::Digitize(){

	// create the digits collection
	m_digitsCollection = new AllPixFEI4DigitsCollection("AllPixFEI4Digitizer", collectionName[0] );

	// get the digiManager
	G4DigiManager * digiMan = G4DigiManager::GetDMpointer();

	// BoxSD_0_HitsCollection
	G4int hcID = digiMan->GetHitsCollectionID(m_hitsColName[0]);

	AllPixTrackerHitsCollection * hitsCollection = 0;
	hitsCollection = (AllPixTrackerHitsCollection*)(digiMan->GetHitsCollection(hcID));

	// temporary data structure
	map<pair<G4int, G4int>, G4double > pixelsContent;
	pair<G4int, G4int> tempPixel;

	G4int nEntries = hitsCollection->entries();

	// Example of detector description handle
	// provided by the interface
	AllPixGeoDsc * gD = GetDetectorGeoDscPtr();
	gD->GetNPixelsX();

      //  tin = new TFile("In_Pixel.root","UPDATE");
        double ran=0;
        total_iter=total_iter+1;
        int flag=0,flag1=0;
        int NpX=0,NpY=0;
	for(G4int itr  = 0 ; itr < nEntries ; itr++) {
        flag=0;
	G4double xCoord=0,x4=0;
        G4double yCoord=0,y4=0;
        if(itr>0){
        NpX=(*hitsCollection)[itr-1]->GetPixelNbX();
        NpY=(*hitsCollection)[itr-1]->GetPixelNbY();
        }      
        flag1=0;
        if((NpX==(*hitsCollection)[itr]->GetPixelNbX() && NpY==(*hitsCollection)[itr]->GetPixelNbY()) || (NpX==(*hitsCollection)[itr]->GetPixelNbX()+1 && NpY==(*hitsCollection)[itr]->GetPixelNbY()) || NpX==(*hitsCollection)[itr]->GetPixelNbX() && (NpY==(*hitsCollection)[itr]->GetPixelNbY()+1) || (NpX==(*hitsCollection)[itr]->GetPixelNbX()-1 && NpY==(*hitsCollection)[itr]->GetPixelNbY()) || (NpX==(*hitsCollection)[itr]->GetPixelNbX() && NpY==(*hitsCollection)[itr]->GetPixelNbY()-1)   )flag1=1;


        if(hcID==0){
        TRandom* random = new TRandom;
        random->SetSeed(0);
        ran=random->Rndm();
        xCoord = (*hitsCollection)[itr]->GetPosWithRespectToPixel().x();
        yCoord = (*hitsCollection)[itr]->GetPosWithRespectToPixel().y();
      //  if(std::pow(xCoord/0.05,2)+std::pow(yCoord/0.005,2)>1) continue; ellipse


/*
        //ROI inside the pixel
        if((xCoord<0.125 && xCoord>0.100) || (xCoord<0.050 && xCoord>-0.050) || (xCoord<-0.100 && xCoord>-0.125)){
        if(ran<0.2) continue;
        }
        if(((xCoord<0.100 && xCoord>0.050) || (xCoord<-0.050 && xCoord>-0.100)) && (yCoord>0.010 || yCoord<-0.010)){
        if(ran<0.2) continue;
        }


        if(((xCoord<0.100 && xCoord>0.050) || (xCoord<-0.050 && xCoord>-0.100)) && (yCoord<0.010 || yCoord>-0.010)){
        if(ran>0.2) continue;
   

       } */

/*
       if((xCoord<0.125 && xCoord>0.100)  || (xCoord<0.075 && xCoord>0.060) || (xCoord<0.025 && xCoord>0.020) || (xCoord<-0.023 && xCoord>-0.024) ) {
              flag=1;

         }
  
*/


      if((yCoord<0.025 && yCoord>0.017)  || (yCoord>-0.004 && yCoord<0.004)  || (yCoord>-0.020 && yCoord<-0.018) ) {
        flag=1;
           }

        if(flag==0 || flag1==1 )continue;
  //      if(std::pow(xCoord/0.05,2)+std::pow(yCoord/0.01,2)>1) continue ; //ellipse
      //  if(std::pow(xCoord,2)+std::pow(yCoord,2)>0.0004) continue;     //circle
         X.push_back(xCoord*1000+125);
         Y.push_back(yCoord*1000+25);

        std::cout<<(*hitsCollection)[itr]->GetPosWithRespectToPixel().x()<<std::endl; 
         }



                      if(hcID==4){
                        X1.push_back((*hitsCollection)[itr]->GetPosWithRespectToPixel().x());
                        Y1.push_back((*hitsCollection)[itr]->GetPosWithRespectToPixel().y());
                       }




       		tempPixel.first  = (*hitsCollection)[itr]->GetPixelNbX();
		tempPixel.second = (*hitsCollection)[itr]->GetPixelNbY();
		pixelsContent[tempPixel] += (*hitsCollection)[itr]->GetEdep();


      }



	if(total_iter==100000 && hcID==0){
         TFile *tin;
         h  = new TH2F("h","IN_PIXEL_OCCUPANCY_SIMULATION_DUT",250,0,250,50,0,50);
         tin = new TFile("In_Pixel.root","RECREATE");
         for(unsigned int i=0; i<X.size();i++){
         h->Fill(X[i],Y[i]);      }
         h->Write();
         tin->Close();
          }
         if(total_iter==100000 && hcID==4){
         TFile *tin1;
         tin1 = new TFile("In_Pixel.root","UPDATE");

         h1  = new TH2F("h1","IN_PIXEL_OCCUPANCY_SIMULATION_Plane",250,-0.125,0.125,50,-0.025,0.025);

         for(unsigned int i=0; i<X1.size();i++){
         h1->Fill(X1[i],Y1[i]);      }
         h1->Write();
         tin1->Close();
          }










 	// Now create digits, one per pixel
	// Second entry in the map is the energy deposit in the pixel
	map<pair<G4int, G4int>, G4double >::iterator pCItr = pixelsContent.begin();

	// NOTE that there is a nice interface which provides useful info for hits.
	// For instance, the following member gives you the position of a hit with respect
	//  to the center of the pixel.
	// G4ThreeVector vec = (*hitsCollection)[itr]->GetPosWithRespectToPixel();
	// See class AllPixTrackerHit !

	// Also, you have full access to the detector geometry from this scope
	// AllPixGeoDsc * GetDetectorGeoDscPtr()
	// provides you with a pointer to the geometry description.
	// See class AllPixGeoDsc !









       
	for( ; pCItr != pixelsContent.end() ; pCItr++)
	{ 
		
                if((*pCItr).second > m_digitIn.thl) // over threshold !
		{
                          



			// Create one digit per pixel, I need to look at all the pixels first
			AllPixFEI4Digit * digit = new AllPixFEI4Digit;
			digit->SetPixelIDX((*pCItr).first.first);
			digit->SetPixelIDY((*pCItr).first.second);
			digit->IncreasePixelCounts(); // Counting mode

			m_digitsCollection->insert(digit);
                  
		}
	}

	G4int dc_entries = m_digitsCollection->entries();
	if(dc_entries > 0){
		G4cout << "--------> Digits Collection : " << collectionName[0]
		                                           << "(" << m_hitsColName[0] << ")"
		                                           << " contains " << dc_entries
		                                           << " digits" << G4endl;
	}

	StoreDigiCollection(m_digitsCollection);


}
