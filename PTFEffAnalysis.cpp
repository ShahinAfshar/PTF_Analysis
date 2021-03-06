#include "PTFQEAnalysis.hpp"
#include "ScanPoint.hpp"
#include "WaveformFitResult.hpp"

using namespace std;

PTFQEAnalysis::PTFQEAnalysis( TFile *outfile, PTFAnalysis *ptfanalysis ){

  vector< double > xbins = ptfanalysis->get_bins( 'x' );
  vector< double > ybins = ptfanalysis->get_bins( 'y' );
  //Create detection efficiency histogram
  d_efficiency = new TH2D("d_efficiency", "Detection efficiency", xbins.size()-1, &xbins[0], ybins.size()-1, &ybins[0]);
  d_efficiency->GetXaxis()->SetTitle("X position on PMT(m)");
  d_efficiency->GetYaxis()->SetTitle("Y position on PMT(m)");
  d_efficiency->GetXaxis()->CenterTitle();
  d_efficiency->GetYaxis()->CenterTitle();
  vector<double> numbers;
  double number;

  ifstream myfile("example.txt"); //file opening constructor

  //Operation to check if the file opened
  if ( myfile.is_open() ){
    
    while(myfile >>number ){

      //putting data into the vector
      numbers.push_back(number);
          

    }
  }
  //   Conversion of vector to array 
  int n=numbers.size();
  double b[n];
   for (int i=0; i<numbers.size();i++){
     b[i]=numbers.at(i);
  // double b[5]={1,2,3,4,5};
  //for(int i=0; i<5;i++){
    if (b[i]==0.82848){
      cout<<"GOOOOOOOODDDDDD"<<i<<endl;
    break;
    }
  }


  vector<ScanPoint>scanpoints=ptfanalysis->get_scanpoints();
  for(unsigned int iscan=0; iscan<scanpoints.size(); iscan++){
    ScanPoint scanpoint = scanpoints[iscan];
    long long entry = scanpoint.get_entry();
    
    
    //Loop through fit results
    for(unsigned long long iwavfm=0; iwavfm<scanpoint.nentries(); iwavfm++){
      entry += iwavfm;
      const WaveformFitResult fit_result = ptfanalysis->get_fitresult(iscan, iwavfm);
    
      double  efficiency1=(double)fit_result.haswf/(double)scanpoint.nentries();
	 
      int index = iscan/20;
      
        d_efficiency->Fill(fit_result.x, fit_result.y,efficiency1);
      
     
      
    
    }
   
     
  }
  //Getting the desired scan point (Maximum efficiency corresponding point)
  double  maxi=d_efficiency->GetBinContent(d_efficiency->GetMaximumBin());
  int maxbinnumber=d_efficiency->GetMaximumBin();
  cout<<"THIS IS WHAT WE ARE LOOKING FOR"<<maxbinnumber<<endl;
  cout<<"This is the point you are looking for?"<< d_efficiency->GetMaximumBin()<<endl;
  cout <<"The maximum value of efficency is"<<maxi<<endl;
  // Int_t x,y,z;
  //  d_efficiency->GetBinXYZ(maxi, x, y,z);
  //  printf("The bin having the maximum value is (%d,%d)\n",x,y);
  double a[36];
  for (int i = 0; i <d_efficiency->GetSize(); i++){
     double eff= d_efficiency->GetBinContent(i);
     cout<<"THIS IS YOUR EFFICIENCY"<< eff<<endl;
     ofstream Myeff;
     Myeff.open ("me.txt",ios::app);
     if (eff!=0){
       Myeff<<eff<<endl;
     }

       //   ifstream Youreff("MYEFFICIENCY.txt"); //file opening constructor

  //Operation to check if the file opened
     /*  if ( Youreff.is_open() ){
    
    while(Youreff >>number ){

      //putting data into the vector
      numbers.push_back(number);
          

    }
  }
  //   Conversion of vector to array 
  int n=numbers.size();
  double a[n];
   for (int i=0; i<numbers.size();i++){
     a[i]=numbers.at(i);
  // double b[5]={1,2,3,4,5};
  //for(int i=0; i<5;i++){
    if (a[i]==0.228174){
      cout<<"MAN AMADEAM"<<i<<endl;
    break;
    }
    }*/
  // unsigned int iscan;
   //  double point=0;
  // double a[37];
  // for(unsigned iscan=0; iscan<scanpoints.size(); iscan++){
     // vector<double> v;
     // a[i]= d_efficiency->GetBinContent(i);
    
     // if(a[i]==0.228174){
    // }
     //  int k=v.size();
     // double a[k];
  
    
     //   for (int j=0; j<v.size();j++){
     //  a[j]=v.at(j);
      //  if (d_efficiency->GetBinContent(iscan)==0.228174){
     //  if(v.at(iscan)==0.228174){
   // if (d_efficiency->GetBinContent(iscan)>point)
   // point =d_efficiency->GetBinContent(iscan);
     // cout <<"Highest efficiency is in "<<i<<endl;
      	      // point+=d_efficiency->GetBinContent(iscan);
     // break;
     // }
}
   }
    //  }
    //	cout<<"My desired scan point  is"<<iscan<<endl;

    



