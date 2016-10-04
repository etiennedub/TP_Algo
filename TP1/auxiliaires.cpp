
/*
 * auxiliaires.cpp
 *
 *  Created on: 2016-09-14
 *      Author: etudiant
 */
#include "auxiliaires.h"

std::vector<std::string> split(const std::string &s, char delim){
	std::vector<std::string> resultat;
	std::string mot = "";

	for(int i = 0; i < s.length(); i++){
		if (char(s[i]) == delim){
			resultat.push_back(mot);
			mot = "";
		}
		else{
			mot += s[i];
		}
	}

	resultat.push_back(mot);
	return resultat;
}

void lireFichier(std::string nomFichier,
		std::vector<std::vector<std::string>>& resultats, char delimiteur, bool rm_entete){

	std::string ligne;
	std::ifstream fichier;
	fichier.open(nomFichier);

	if (fichier.is_open()){

		while ( getline(fichier, ligne)){
			resultats.push_back(split(ligne, delimiteur));
		}
		fichier.close();
		if (rm_entete){
			resultats.erase(resultats.begin());
		}
	}

	else{
		// Exception ici  ***************
		std::cout << "Unable to open file";
	}
}

	Heure::Heure(){
		long temps = time(0);
		m_heure = (temps/(60 * 60)) % 24 - 4;
		m_min = (temps/(60 )) % 60;
		m_sec =  temps % 60;
	}

	Heure::Heure(unsigned int heure, unsigned int min, unsigned int sec){
		if (heure <= 30 and min <= 59 and sec <= 59){
			m_heure = heure;
			m_min = min;
			m_sec = sec;
		}
		else{
			// Exception ici  ***************
			std::cout << "Time invalide";
		}
	}

	Heure Heure::add_secondes(unsigned int secs){
		if (m_sec + secs <= 60){
			m_sec = m_sec + secs;
		}
		else{
			int ajout_min = (m_sec + secs) / 60;
			m_sec = ( m_sec + secs) % 60;

			if (m_min + ajout_min <= 60){
				m_min = m_min + ajout_min;
			}

			else{
				int ajout_heure = (m_min + ajout_min) / 60;
				m_min = (m_min + ajout_min) % 60;

				if (m_heure + ajout_heure <= 30){
					m_heure = m_heure + ajout_heure;
					}
				else{
					m_heure = m_heure + ajout_heure;
					// Exception ici  ***************
					std::cout << "Hour over 30";
				}
			}
		}
	}

	bool Heure::operator== (const Heure & other) const{
		return(m_heure == other.m_heure and m_min == other.m_min
				and m_sec == other.m_sec);
	}

	bool Heure::operator> (const Heure & other) const{
		bool resultat;
		if (m_heure > other.m_heure){
			resultat = true;
		}
		else{
			if (m_min > other.m_min){
				resultat = true;
			}
			else{
				if (m_sec > other.m_sec){
					resultat = true;
				}
				else{
					resultat = false;
				}
			}
		}
		return resultat;
	}
	bool Heure::operator< (const Heure & other) const{
		bool resultat;
		if (m_heure < other.m_heure){
			resultat = true;
		}
		else{
			if (m_min < other.m_min){
				resultat = true;
			}
			else{
				if (m_sec < other.m_sec){
					resultat = true;
				}
				else{
					resultat = false;
				}
			}
		}
		return resultat;
	}
	bool Heure::operator<= (const Heure & other) const{
		bool resultat;
		if (m_heure <= other.m_heure){
			resultat = true;
		}
		else{
			if (m_min <= other.m_min){
				resultat = true;
			}
			else{
				if (m_sec <= other.m_sec){
					resultat = true;
				}
				else{
					resultat = false;
				}
			}
		}
		return(resultat);
	}

	bool Heure::operator>= (const Heure & other) const{
		bool resultat;
		if (m_heure >= other.m_heure){
			resultat = true;
		}
		else{
			if (m_min >= other.m_min){
				resultat = true;
			}
			else{
				if (m_sec >= other.m_sec){
					resultat = true;
				}
				else{
					resultat = false;
				}
			}
		}
		return(resultat);
	}

	int Heure::operator- (const Heure & other) const{
		int resultat = (m_heure - other.m_heure) * 3600
				+ (m_min - other.m_min) * 60
				+ m_sec - other.m_sec;
		return(resultat);
	}

	std::ostream & operator<<(std::ostream & flux, const Heure & p_heure){
		if (p_heure.m_heure < 10){
			flux << "0";
		}
		flux << p_heure.m_heure << ":";
		if (p_heure.m_min < 10){
			flux << "0";
		}
		flux << p_heure.m_min << ":";
		if (p_heure.m_sec < 10){
				flux << "0";
		}
		flux << p_heure.m_sec;
		return flux;
	}

	Date::Date(){
		time_t now = time(0);
		tm *ltm = localtime(&now);
		m_an = ltm->tm_year;
		m_mois = ltm->tm_mon;
		m_jour = ltm->tm_mday;
	}

	Date::Date(unsigned int an, unsigned int mois, unsigned int jour){
		if (valideDate(an, mois, jour)){
			m_an = an;
			m_mois = mois;
			m_jour = jour;
		}
		else{
			std::cout << "Date non valide";
		}
	}

	bool Date::valideDate (unsigned int an, unsigned int mois, unsigned int jour) const{
		  if (! (1<= mois && mois<=12) )
		     return false;
		  else if (! (1<= jour && jour<=31) )
		     return false;
		  else if ( (jour==31) && (mois==2 || mois==4 || mois==6 || mois==9 || mois==11) )
		     return false;
		  else if ( (jour==30) && (mois==2) )
		     return false;
		  else if ( (mois==2) && (jour==29) && (an%4!=0) )
		     return false;
		  else if ( (mois==2) && (jour==29) && (an%400==0) )
		     return true;
		  else if ( (mois==2) && (jour==29) && (an%100==0) )
		     return false;
		  else if ( (mois==2) && (jour==29) && (an%4==0)  )
		     return true;
	}
	bool Date::operator== (const Date & other) const{
		return(m_an==other.m_an && m_mois==other.m_mois && m_jour==other.m_jour);
	}
	bool Date::operator< (const Date & other) const{
		if (m_an<other.m_an){
			return true;
		}
		else{
			if (m_mois<other.m_mois){
					return true;
			}
			else{
				if (m_mois<other.m_mois){
						return true;
				}
				else{
					return false;
				}
			}
		}
	}
	bool Date::operator> (const Date & other) const{
		if (m_an>other.m_an){
			return true;
		}
		else{
			if (m_mois>other.m_mois){
					return true;
			}
			else{
				if (m_mois>other.m_mois){
						return true;
				}
				else{
					return false;
				}
			}
		}
	}
	std::ostream & operator<<(std::ostream & flux, const Date & p_date){
		flux << p_date.m_an << "-" << p_date.m_mois << "-" << p_date.m_jour;
		return flux;
	}
