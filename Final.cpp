#include<iostream>
#include<vector>
#include <limits>
#include<fstream>
#include <ctime>

using namespace std;

int main(){
	 
	int totalPlane;		//counter of plane to be analyzed
	int ict; 			//interval count for each Plane
	string pidtemp;		
	char color;
	
	//vector variable for later analysis
	vector<string> anal_plane_id;
	vector<double> anal_avg_v;
	
	//variables for fastest and slowest velocity and plane ID
	double vfastest=0, vslowest=9999999;
	string pfastest, pslowest;
	double sum, avg;
	
	//variables for sorting planes according to average speed
	double sort_avg;
	string sort_name;
	
	ifstream infile;
	ofstream outfile;
	
	infile.open("https://utpmy-my.sharepoint.com/:t:/g/personal/muhammad_18002292_utp_edu_my/EQaCT1K4UL5Flfygpme-EysBZMTLXao_hYKo17F2b26LGQ?e=fzEp9X");
	outfile.open("C:output.txt");

	cout<<"========================================================"<<endl;
	cout<<"\t---WELCOME TO PLANE ANALYSIS PROGRAM---"<<endl;
	cout<<"========================================================"<<endl;
	cout<<"\t\t       __|__"<<endl;
	cout<<"\t\t--o--o--(_)--o--o--"<<endl;
	
	cout<<"\nThis program will automatically calculate for average speed of plane by their: "<<endl;
	cout<<"\t1. Presure at Ram Port \n\t2. Pressure at Static Port \n\t3. Altitude"<<endl;
	cout<<"\nPress Enter to Continue:";
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	
	cout<<"\nCalculating velocity..."<<endl;
	cout<<"Summing up velocity..."<<endl;
	cout<<"Calculating average velocity..."<<endl;
	cout<<"Sorting..."<<endl;
	cout<<"..."<<endl;
	cout<<".."<<endl;
	cout<<"."<<endl;
	cout<<"             _____"<<endl;
	cout<<"            _|_~-|___"<<endl;
	cout<<"    =  = ==(____AA____D"<<endl;
	cout<<"                |_____|___________________,-~~~~~~~`-.._"<<endl;
	cout<<"               /|     o O o o o o O O o o o o o o O o  ||_"<<endl;
	cout<<"                `~-.__        ___..----..                  )"<<endl;
	cout<<"                      `---~~|___________/------------`````"<<endl;
	cout<<"                      =  ===(_________D"<<endl;
	cout<<"\nCalculation done ! Data can be viewed in the output file."<<endl;
	
	// current date/time based on current system
	time_t now = time(0);

	// convert now to string form
	char* dt = ctime(&now);
	
	cout<<"\n\n--------------------------------------------------------------"<<endl;
	cout<<"Successfully write the output file on "<<dt<<endl;
	
	infile>>totalPlane; 									//read number of total plane
	
	for(int i=0; i<totalPlane; i++){ 						//loop dont stop until all plane recorded
		
		infile>>pidtemp; 
		infile>>ict; 										//read how many time interval
		
		vector<int> time(ict);
		vector<double> p1(ict);
		vector<double> p2(ict);
		vector<double> v(ict);
		vector<double> alt(ict);
		vector<double> dens(ict);
		
		sum = 0;											//reset sum value
		
		for(int i=0; i<ict; i++){
			
			infile>>time[i]; 								//time in 24hours system
			infile>>p1[i]; 									//pressure in pascal
			infile>>p2[i];
			infile>>alt[i]; 								//read altitude to determine the air density
			
			if (alt[i] >= 0 && alt[i] < 1000)				//altitude above sea level 								
				dens[i] = 1.225;
			else if (alt[i] >= 1000 && alt[i] < 2000)
				dens[i] = 1.112;
			else if (alt[i] >= 2000 && alt[i] < 3000)
				dens[i] = 1.007;
			else if (alt[i] >= 3000 && alt[i] < 4000)
				dens[i] = 0.9093;
			else if (alt[i] >= 4000 && alt[i] < 5000)
				dens[i] = 0.8194;
			else if (alt[i] >= 5000 && alt[i] < 6000)
				dens[i] = 0.7364;
			else if (alt[i] >= 6000 && alt[i] < 7000)
				dens[i] = 0.6601;
			else if (alt[i] >= 7000 && alt[i] < 8000)
				dens[i] = 0.5900;
			else if (alt[i] >= 8000 && alt[i] < 9000)
				dens[i] = 0.5258;
			else if (alt[i] >= 9000 && alt[i] < 10000)
				dens[i] = 0.4671;
			else if (alt[i] >= 10000 && alt[i] < 15000)
				dens[i] = 0.4135;
			else
				dens[i] = 0.1948;
				
			v[i]=(2*(p1[i]-p2[i])/dens[i]);  				//calculate plane velocity using fm bernoulli
			sum+=v[i];
			
			}
			
		avg=sum/ict;
			
		anal_plane_id.push_back(pidtemp);					//store plane ID into vector type variables
		anal_avg_v.push_back(avg);							//store average speed into vector type variables
		
		outfile<<"======================================="<<endl;	
		outfile<<"\tPlane ID: "<<pidtemp<<endl;
		outfile<<"======================================="<<endl;
		
		for(int i=0; i<ict; i++){
			outfile<<"Time of Flight #"<<(i+1)<<": "<<time[i]<<"hrs"<<endl;	
			outfile<<"Velocity #"<<(i+1)<<": "<<v[i]<<" km/h"<<endl<<endl;
		}
				
		outfile<<"Average Velocity: "<<avg<<" km/h"<<endl;
		outfile<<"---------------------------------------"<<endl<<endl;	
	}
		
	for(int i=0; i < totalPlane; i++){
		
		//analyse for fastest plane
		if (anal_avg_v[i]>vfastest){
				vfastest = anal_avg_v[i];
				pfastest=anal_plane_id[i];
			}
		
		//anaylze for slowest plane		
		else if (anal_avg_v[i]<vslowest){
				vslowest = anal_avg_v[i];
				pslowest=anal_plane_id[i];
			}
	}
	
	//sorting plane according to increasing average speed
	for(int i=0; i < totalPlane; i++){				
		for(int j = (totalPlane-1); j >= 0; j--){
			if(anal_avg_v[j] < anal_avg_v[j-1]){
				sort_avg = anal_avg_v[j];
				anal_avg_v[j] = anal_avg_v[j-1];
				anal_avg_v[j-1] = sort_avg;
				
				sort_name = anal_plane_id[j];
				anal_plane_id[j] = anal_plane_id[j-1];
				anal_plane_id[j-1] = sort_name;
			}
		}
	}
	
	outfile<<"                             |"<<endl;
	outfile<<"                             |"<<endl;
	outfile<<"                             |"<<endl;
	outfile<<"                           .-'-."<<endl;
	outfile<<"                          ' ___ '"<<endl;
	outfile<<"                ---------'  .-.  '---------"<<endl;
	outfile<<"_________________________'  '-'  '_________________________"<<endl;
	outfile<<" ''''''-|---|--|    |==][^',_m_,'^][==|    |--|---|-''''''"<<endl;
	outfile<<"               |    |  || |  H  | ||  |    |"<<endl;
	outfile<<"                '--'   OO   O|O   OO   '--'"<<endl;
	
	outfile<<"\nSorted plane ID in acsending order of their average speed :-"<<endl;
	outfile<<"\n| ";
	
	for(int i=0; i < totalPlane; i++)
		outfile<<anal_plane_id[i]<<"( "<<anal_avg_v[i]<<" km/h )"<<" | ";
	
	cout<<endl;
	
	outfile<<"\n\nFastest plane is "<<pfastest<<" with speed of "<<vfastest<<" km/h"<<endl;
	outfile<<"\nSlowest plane is "<<pslowest<<" with speed of "<<vslowest<<" km/h"<<endl;
	
	outfile<<"\n\n-----------------------------------------------"<<endl;
	outfile<<"Data stored in file on "<<dt;
	
	
	
	return 0;
}
