/*
 * Lab1EC.c
 *
 *  Created on: Feb 19, 2023
 *      Author: kjaccola
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int preferences[10][5];//read in to duplicate file array
int selection[5];//to hold final selection
int placed = 0;//count the number of programmers placed
int deptTop[5];



int main(){
char userinput[20];
FILE* textfile;
char line[10];
char number[12];
int smallarray[5];
printf("Input the name of the file to be read: \n");
scanf("%s", &userinput);
textfile = fopen(userinput, "r");
int num = 0;

while(EOF !=fscanf(textfile,"%d %d %d %d %d", &smallarray[0], &smallarray[1],&smallarray[2],&smallarray[3],&smallarray[4])){
	for(int i = 0; i<5; i++){
		preferences[num][i]= smallarray[i];
	}

	num++;
}
fclose(textfile);


for(int i = 0; i<5; i++){
	deptTop[i]= preferences[0][i];
}

placement();

}
void placement(){
while(placed<5){//until five departments have their placements
for(int dept = 0; dept <5; dept++){//starting at department1 and moving right
	if(selection[dept]!= 0)continue;//if that department is alredy placed
	int duplicate = 0;
	for (int otherdept = 0; otherdept<5; otherdept++){
		if(dept==otherdept)continue;
		if (deptTop[dept] == deptTop[otherdept]){
			duplicate ++;//finding if theirs other depts with the same first choice
		}
	}
	if(duplicate == 0){//if no competition
		placed ++;
		selection[dept] = deptTop[dept];//set the selection array for depts

	}
	else{
		int winner = dept;//to start with the one you are currently checking
		for(int other = 0; other<5; other++){//checking all depts
			if (other == dept)continue;
			else{
				if (deptTop[dept]==deptTop[other]){//both depts have same first choice
					if(programmersChoice(winner, other,deptTop[dept])==other)winner = other;
				}
			}
		}
		selection[winner]= deptTop[dept];
		placed++;
		for(int j = 0; j<5; j++){
			if(selection[j]!=0)continue;
			if(deptTop[j] == selection[winner]){
				int wrong = 1;
				while(wrong != 0){
					for(int k = 0; k<5; k++){
						if(preferences[k][j]== deptTop[j]){
							deptTop[j]= preferences[k+1][j];
							break;
						}
					}
					int dupe = 0;
					for(int n = 0; n<5; n++){
						if(selection[n]== deptTop[j])dupe++;
					}
					if(dupe == 0)wrong = 0;
				}
			}
	    }

	}
}
}
printf("Department #1 will get Programmer #%d\n", selection[0]);
printf("Department #2 will get Programmer #%d\n", selection[1]);
printf("Department #3 will get Programmer #%d\n", selection[2]);
printf("Department #4 will get Programmer #%d\n", selection[3]);
printf("Department #5 will get Programmer #%d\n", selection[4]);

}
int programmersChoice( int deptcol1, int deptcol2, int programmer){
	for(int i = 5; i<10; i++){
		if(preferences[i][programmer-1]==deptcol1+1)return deptcol1;
		if(preferences[i][programmer-1]==deptcol2+1)return deptcol2;

	}
}


