//Masato Kato
//4/28/25

#include <stdio.h>
#include <stdbool.h>

#define MAX_GNUM 6
#define W_LEN 5

void read_it_fromthefile(char word[]);
void ur_valid_input(char guess[]);
bool its_VALID_guess(char guess[]);
void print_guess(char guesses[MAX_GNUM][W_LEN +1], char display[MAX_GNUM][W_LEN + 1],int guess_count);
void process_guess(char guess[], char word[], char display[]);
bool is_right_guess(char guess[], char word[]);
void to_lowercase(char guess[]);

int main(){
	char word[W_LEN + 1];
	char guess[W_LEN + 1];
	char guesses[MAX_GNUM][W_LEN + 1];
	char display[MAX_GNUM][W_LEN + 1];
	int guess_count = 0;
	bool win = false;
	
	
	read_it_fromthefile(word);
	while (guess_count < MAX_GNUM && !win) {
		printf("GUESS %d! Enter your guess: ", guess_count + 1);
		ur_valid_input(guess);
		to_lowercase(guess);
		
		for(int i=0; i<W_LEN; i++){
			guesses[guess_count][i]= guess[i];
		}
		guesses[guess_count][W_LEN] = '\0';
		
		process_guess(guess, word, display[guess_count]);
		print_guess(guesses, display, guess_count + 1);
		
	if(is_right_guess(guess, word)){
		for (int i = 0; i < 8; i++) 
			printf(" ");
		for (int i = 0; i < W_LEN; i++) {
			printf("%c", guess[i] - 32);
		}
			printf("\n");
		for (int i = 0; i < 8; i++) printf(" ");
			printf("You won in %d guesses!\n", guess_count + 1);
		for (int i = 0; i < 16; i++) printf(" ");
			printf("GOATED!\n");
		win = true;
		}
		guess_count++;
	}	
	if(!win){
		printf("Final Guess: ");
		for (int i = 0; i < W_LEN; i++) {
            	char c = guess[i];
            	if (c >= 'a' && c <= 'z') c = c - 32;
            	printf("%c", c);
        	}
        	printf("\n");
        print_guess(guesses, display, guess_count);
        printf("You lost, better luck next time!\n");
    }
	
return 0;
}

void read_it_fromthefile(char word[]){
	FILE *file = fopen("word.txt", "r");
    	if (file == NULL) {
        	printf("Error: Could not open word.txt\n");
        	word[0] = '\0';
        return;
    	}
    	for (int i = 0; i < W_LEN; i++) {
    		word[i] = fgetc(file);
    	}
    		word[W_LEN] = '\0';
    	fclose(file);
}

void to_lowercase(char guess[]){
	for (int i = 0; i < W_LEN; i++) {
        	if (guess[i] >= 'A' && guess[i] <= 'Z') {
            		guess[i] = guess[i] + 32;
        	}
    	}
}

void ur_valid_input(char guess[]){
	// while (true) {
        //scanf("%s", guess);

        //char ch;
        //while ((ch = getchar()) != '\n' && ch != EOF); We can't use EOF

        //if (its_VALID_guess(guess)) {
            //break;  this whole thing stops everything from reading file 
            //reads even when the word is longer than 6 letters

	
	char line[100]; 

    	while (true) {
        	fgets(line, sizeof(line), stdin); 

        	int i = 0;
        while (line[i] != '\n' && line[i] != '\0' && i < W_LEN) {
            	guess[i] = line[i];
            	
            	
            	
            		i++;
        }
        	guess[i] = '\0';

        	if (its_VALID_guess(guess)) {
            			break;
        } else {
            printf("Please try again: ");
        }
    }
}


bool its_VALID_guess(char guess[]){
	int length = 0;
	bool only_letters = true;

    	while (guess[length] != '\0') {
        	char c = guess[length];
        	if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            		only_letters = false;
        	}
        	length++;
    	}
    	
	if (length != W_LEN) {
        	printf("Your guess must be 5 letters long.");
    	}
    	if (!only_letters) {
    		printf("Your guess must contain only letters.\nPlease try again: ");
        	return false;
    	}

    	if (length != W_LEN) {
        	printf("\nPlease try again: ");
        	return false;
    	}
    	return true;
}
void print_guess(char guesses[MAX_GNUM][W_LEN +1], char display[MAX_GNUM][W_LEN + 1],int guess_count){
    		printf("================================\n");
    	for (int i = 0; i < guess_count; i++) {
        for (int j = 0; j < W_LEN; j++) {
            	if (display[i][j] == 'C') {
                
                char c = guesses[i][j];
                if (c >= 'a' && c <= 'z') {
                    c = c - 32;
                }
                	printf("%c", c);
            	} else {
                	printf("%c", guesses[i][j]);
            	}
        }
        	printf("\n");
        for (int j = 0; j < W_LEN; j++) {
            	if (display[i][j] == 'I') {
                	printf("^");
            	} else {
                	printf(" ");
            	}
        }
        printf("\n");
    }
}
void process_guess(char guess[], char word[], char display[]){
bool used[W_LEN] = {false};  

    	for (int i = 0; i < W_LEN; i++) {
        	if (guess[i] == word[i]) {
            		display[i] = 'C';
            		used[i] = true;
        	} else {
            		display[i] = ' ';
        	}
    	}

    	for (int i = 0; i < W_LEN; i++) {
        	if (display[i] == 'C') continue;
        		for (int j = 0; j < W_LEN; j++) {
            	if (!used[j] && guess[i] == word[j]) {
                	display[i] = 'I';
                	used[j] = true;
                break;
            	}
        		}
    	}
}

bool is_right_guess(char guess[], char word[]){
	bool used[W_LEN];
	for (int i = 0; i < W_LEN; i++) {
    		used[i] = false;
	}
	for (int i = 0; i < W_LEN; i++) {
        	if (guess[i] != word[i]) {
            	return false;
        	}
    	}
    	
    return true;
}
