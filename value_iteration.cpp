#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main(){
	// print board
	cout << " Team X Map" << '\n';
	cout << "-X" << " " << "0" << " " << "0" << " " << "0" << "\n";
	cout << "0" << " " << "0" << " " << "W" << " " << "0" << "\n";
	cout << "-X/10" << " " << "0" << " " << "0" << " " << "0" << "\n";
	cout << "0" << " " << "X/10" << " " << "0" << " " << "X" << "\n\n";

	int iter_count = 1;
	float temp1=0,temp2=0,temp3=0,temp4=0,temp5=0,temp6=0,temp7=0;
	int p=0,q=0,i=0,j=0,k=0;
	float change=0.0, maxchange=0.0;
	int N=0,M=0;
	// cout << "Enter dimensions of grid: ";
	cin >> N >> M;
	// cout << N << " " << M << "\n";
	float grid[N][M];
	float Ut[N][M];
	float New_Ut[N][M];
	float cp_mat[N][M];
	int wall_flag[N][M];
	int endSflag[N][M];
	float U_left = 0, U_right = 0, U_up = 0, U_down = 0;
	float Old_Ut = 0;
	float temp = 0;

	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			cin >> grid[i][j];
			Ut[i][j] = grid[i][j];
			New_Ut[i][j] = Ut[i][j];
			cp_mat[i][j] = Ut[i][j];
		}
	}


	std::cout << " Matrix after Itration 0" << '\n';
	cout << "-----------------\n";
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			cout << New_Ut[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "-----------------\n";

	int E=0,W=0;
	// cout << "Number of End States and Walls: ";
	cin >> E >> W;

	int ends[E][2];
	int wall[W][2];
	// initialize flags
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			endSflag[i][j] = 0;
			wall_flag[i][j] = 0;
		}
	}


	for(i=0;i<E; i++){
		cin >> ends[i][0] >> ends[i][1];
		endSflag[ends[i][0]][ends[i][1]] = 1;
		cp_mat[ends[i][0]][ends[i][1]] = 0;
	}

	for(i=0;i<W; i++){
		cin >> wall[i][0] >> wall[i][1];
		wall_flag[wall[i][0]][wall[i][1]] = 1;
	}

	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			Ut[i][j]-=cp_mat[i][j];
			New_Ut[i][j]-=cp_mat[i][j];
		}
	}

	int start[2];
	cin >> start[0] >> start[1];

	float step_reward = 0;
	// cout << "Enter Step Reward: ";
	cin >> step_reward;

	// cout << step_reward << "\n";
maxchange = 1; int flag_maxchange=0;


	while(maxchange > 0.01){
		iter_count++;
		// how to change maxchange

		if(flag_maxchange == 0){
			flag_maxchange = 1;
			maxchange = 0;
		}


		maxchange = 0;
		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
				Old_Ut = Ut[i][j];
				change = 0;


				if(wall_flag[i][j]==0 && endSflag[i][j]==0){
					// print utility state
					std::cout << "Utility State: " << "(" <<  i << " " << j << ")\n";

					temp = Old_Ut;
					if(j-1<0 || wall_flag[i][j-1] == 1)
						U_left = Ut[i][j] + cp_mat[i][j];
					else
						U_left = Ut[i][j-1] + cp_mat[i][j-1];


					if(j+1>=M || wall_flag[i][j+1] == 1)
						U_right = Ut[i][j] + cp_mat[i][j];
					else
						U_right = Ut[i][j+1] + cp_mat[i][j+1];


					if(i-1<0 || wall_flag[i-1][j] == 1)
						U_up = Ut[i][j] + cp_mat[i][j];
					else
						U_up = Ut[i-1][j] + cp_mat[i-1][j];


					if(i+1>=N || wall_flag[i+1][j] == 1)
						U_down = Ut[i][j] + cp_mat[i][j];
					else
						U_down = Ut[i+1][j] + cp_mat[i+1][j];

					// cout << U_right << " " << U_left << " " << U_up  << " "<< U_down << "\n";

					// downward movement
					// Ut[i][j] = max(temp, step_reward + 0.8*Ut[i+1][j] + 0.1*Ut[i][j-1] + 0.1*Ut[i][j+1]);
					temp1 =  float(0.8*U_down + 0.1*U_left + 0.1*U_right);

					// upward movement
					temp2 =  float(0.8*U_up + 0.1*U_left + 0.1*U_right);

					// leftwardmovement
					temp3 = float(0.8*U_right + 0.1*U_down + 0.1*U_up);

					// rightward leftwardmovement
					temp4 = float(0.8*U_left + 0.1*U_down + 0.1*U_up);

					std::cout << "South: " << temp1 << '\n';
					std::cout << "North: " << temp2 << '\n';
					std::cout << "East: " << temp3 << '\n';
					std::cout << "West: " << temp4 << '\n';

					temp5 = max(temp1, temp2);
					temp6 = max(temp3, temp4);
					temp7 = max(temp5, temp6);
					New_Ut[i][j] = float(step_reward + temp7);
					std::cout << "\nPolicy: " << temp7 << '\n';
					std::cout << "Utility: " << New_Ut[i][j] << "\n\n\n";
				}
				else{
					New_Ut[i][j] = Old_Ut;
				}

				change = abs(New_Ut[i][j] - Ut[i][j]);
				if(change > maxchange){
					maxchange = change;
				}
			}
		}


		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
				Ut[i][j] = New_Ut[i][j];
			}
		}
		cout << '\n';
		std::cout << "Matrix after Iteration " << iter_count << '\n';
		cout << "-----------------\n";
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				cout << New_Ut[i][j] << " ";
			}
			cout << "\n";
		}
		cout << "-----------------\n";
		cout << "\n-----------------\n";
		cout << "maxchange: " << maxchange << "\n";
		cout << "-----------------\n";
	}
	return 0;
}
