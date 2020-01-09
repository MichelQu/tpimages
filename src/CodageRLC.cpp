#include "CodageRLC.h"
#include <iostream>

// Forward declarations
void maj_indices (int& i, int& j);
void ecriture (string& out, int temp, int count, int min_repet);


string CodageRLC (Mat bloc) {
	
	// Indices de parcours de la matrice
	int i = 0, j = 0;
	bool mat_in = true;
	
	// Valeur lue au parcours de la matrice
	int temp = -1;
	// Nombre de r�p�tition courant
	int count = 1;
	// Nombre minimum de r�p�titions pour encodage
	int min_repet = 3;

	// Output string
	string out;

	 while ( mat_in ) {

		

		// Si la valeur courante est �gale � la valeur en m�moire
		if (temp == bloc.at<int>(i,j)) {
			count += 1;
		}

		// Si la valeur courante est diff�rente de la valeur en m�moire
		else {
			ecriture (out, temp, count, min_repet); // Ecriture 
			temp = bloc.at<int>(i,j); // Mise � jour de la valeur courante
			count = 1; // Raz du compteur
		}

		if ( i == 7 && j == 7 ) { // Arriv�e � la fin de la matrice
			if ( count != 1) {
				ecriture (out, temp, count, min_repet); // Ecriture
			}
			mat_in = false;
		} else {
			// Mise � jour de l'indice de parcours
			maj_indices ( i, j );
		}

		//cout << i << ", " << j << " : " << count << endl << endl;

		

	} 
		 
	return out;
}

void maj_indices (int& i, int& j) {

	bool updated = false;

	if ( i == 0 && !updated) { 
		updated = true;
		if ( j % 2 == 0 ) {
			j += 1;
		}
		else {
			i += 1;
			j -= 1;
		}
	}
	if ( i == 7 && !updated) {
		updated = true;
		if ( j % 2 == 0 ) {
			j += 1;
		}
		else {
			i -= 1;
			j += 1;
		}
	}
	if ( j == 0 && !updated) {
		updated = true;
		if ( i % 2 == 0 ) {
			i -= 1;
			j += 1;
		} else {
			i += 1;
		}
	}
	if ( j == 7 && !updated) {
		updated = true;
		if ( i % 2 == 0 ) {
			i += 1;
			j -= 1;
		} else {
			i += 1;
		} 
	}

	if( !updated) {
		if ( (i + j) % 2 == 1 ) {
			i += 1;
			j -= 1;
		} else {
			i -= 1;
			j += 1;
		}
	}
	
}

void ecriture (string& out, int temp, int count, int min_repet) {
	// Si le nombre de valeur compt� est inf�rieur au nombre de repet mini
	if (count < min_repet) {
		// On �crit le nombre de fois qu'on a vu la valeur
		for (int k=0; k < count; k++) {
			out += temp;
		}
	}
	else {
		//cout <<  " print ! " << " : " << count << endl << endl;
		out += '#'; // Indication d'encodage
		out += count; // Nombre de r�p�tition
		out += temp; // Valeur r�p�t�e
	}
}

/*
Mat DecodageRLC (string input_data) {

}*/