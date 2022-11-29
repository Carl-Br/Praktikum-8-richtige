// Datei: liste.cpp

#include <string>
#include "liste.h"

#include <iostream>


std::string liste_als_string(TListenKnoten* anker)
{
    std::string resultat = "";

    if (anker == nullptr) {
        return "Leere Liste.";
    }
    else
    {
        resultat += "[ ";
        TListenKnoten* ptr = anker;
        do
        {
            resultat += std::to_string(ptr->data);

            if (ptr->next != nullptr) { resultat += " , "; }
            else { resultat += " "; }

            ptr = ptr->next;
        } while (ptr != nullptr);
        resultat += "]";
    }
    return resultat;
}

// Wird modifiziert in Aufgabe INF-08.01 ...
void hinten_anfuegen(TListenKnoten* &anker, const int wert)
{
    TListenKnoten* neuer_eintrag = new TListenKnoten;
    neuer_eintrag->data = wert;
    neuer_eintrag->next = nullptr;
    neuer_eintrag->prev = nullptr; 

    if (anker == nullptr) {
        anker = neuer_eintrag;
    }
    else
    {
        TListenKnoten* ptr_next = anker;
        TListenKnoten* ptr_prev = anker; 

        while (ptr_next->next != nullptr) {

            ptr_prev = ptr_next;//der nächste ist jetzt der vorherige
            ptr_next = ptr_next->next;//der nächste springt eines weiter
            // prev pointer
            ptr_next->prev = ptr_prev;//vom nächsten der vorherige ist wird gesetzt
        }
        
        ptr_next->next = neuer_eintrag;//vom letzten der nächste wird aud den neuen Eintrag gesetzt
        ptr_next->next->prev = ptr_prev;//der letzte ist der vorherige vom neuen
    }
}


std::string liste_als_string_rueckwaerts(TListenKnoten* anker) {
    std::string result = ""; 
    
    if (anker == nullptr) {
        return "Leere Liste.";
    }
    else
    {
        TListenKnoten* ptr = anker;
        while (ptr->next != nullptr)
        {
            //springe bis zum ende der Liste
            ptr = ptr->next;
        }

        result += "[ ";
    
        do //liste muss wegen (anker == nullptr) siehe oben mindestens ein element haben
        {
            result += std::to_string(ptr->data);//füge daten an

            if (ptr->prev != nullptr) { result += " , "; }//wenn noch nicht am Ende, dann mach komma
            else { result += " "; }

            ptr = ptr->prev;//spring eins weiter
        } while (ptr != nullptr);//laufe einmal durch
        result += "]";
        
    
    }
    return result;
}


void in_liste_einfuegen(TListenKnoten* &anker, int wert_neu, int vor_wert) {
    
    if (anker == nullptr)//wenn liste leer
    {
        hinten_anfuegen(anker, wert_neu);//füge es einfach norma ein
        return;
    }
    
    //unser neuer knoten
    TListenKnoten* ptr_new = new TListenKnoten;
    ptr_new->data = wert_neu; 
    ptr_new->next = nullptr; 
    ptr_new->prev = nullptr; 

    //Knoten zum suchen. Wenn ein Knoten mit dem gesuchten Wert gefunden wure ist das dieser hier.
    TListenKnoten* ptr_search = anker; 


    bool gefunden = false; //gibt an, ob der Suchwert gefunden wurde

    if (ptr_search != nullptr)
    {

        while (ptr_search->next != nullptr) {//laufe einmal durch

            if (ptr_search->data == vor_wert)//wenn Zielwert gefunden (diese Ifschleife ist für den Fall, dass der Gesuchte Wert an der ersten Stelle steht.)
            {
                gefunden = true;
                break;
            }

            ptr_search = ptr_search->next;
            if (ptr_search->data == vor_wert)
            {
                gefunden = true;
                break;
            }
        }

        if (anker->data == vor_wert)//anker hat den Vorwert
        {

            ptr_new->next = ptr_search;
            ptr_search->prev = ptr_new;
            anker = ptr_new;
            return; 

        }
       
        else if (gefunden)
        {
            //der Knoten ist irgendow in der Liste, nicht außen
            //neuer Knoten wird zwischen temp und ptr_search geschoben

            TListenKnoten* temp;//neuer Knoten
            temp = ptr_search->prev;//temp ist prev vom search
            temp->next = ptr_new;//temp next ist unser neuer Knoten
            ptr_new->next = ptr_search;//...
            ptr_new->prev = temp;
            ptr_search->prev = ptr_new;
            return; 

        }
        
        else if (gefunden == false)
        {

            //hinten_anfuegen(anker, wert_neu); //ich bin j schon einmal "durchgelaufe", deshalb keinene Funktionsaufru (wegem Performance)
            ptr_search->next = ptr_new;
            ptr_new->prev = ptr_search;
        }
       
          

    }
}

void aus_liste_loeschen(TListenKnoten* &anker, int wert) {
    TListenKnoten* ptr = anker; 

    if (anker == nullptr)
    {
       //Leere Liste"
        return; 
    }
    else if (anker->data == wert)
    {
        // anker hat den wert ... 

        //es ist nur er Anker in der Liste
        if (anker->next == nullptr)
        {
            //der anker wird auf 0 gesetzt
            anker = nullptr;
        }
        else
        {
            // es folgen noch werte
            //der Anker wird um eins weiter nach vorne veschoben
            anker = anker->next;
            anker->prev = nullptr;
        }
    }
    else//der anker ist nicht der Wert
    {
       // find the value 
        bool gefunden = false; 
        while (ptr->next != nullptr)//laufe einmal durch
        {

            if (ptr->data == wert)//wenn Zielwert gefunden (diese Ifschleife ist für den Fall, dass der Gesuchte Wert an der ersten Stelle steht.)
            {
                gefunden = true;

                break;
            }

            ptr = ptr->next;
            if (ptr->data == wert)
            {
                gefunden = true;
                break;
            }
        }


        TListenKnoten* temp = ptr; 
        // check position 

        if (ptr->next == nullptr && gefunden ==true )//edgecase am Ende gefunden
        {
            if (ptr->prev != nullptr)
            {
                TListenKnoten* temp; 
                temp = ptr->prev; 
                ptr->prev = nullptr;
                temp->next = nullptr;
                //ptr->prev->next = nullptr;
                
            }
            else
            {
               // anker = nullptr;
                return;
            }
        }
        else if(gefunden)
        {
         // mitte 
            TListenKnoten* temp; 
            temp = ptr; 
            temp = temp->prev; 
            temp->next = ptr->next; 
            ptr->next->prev = temp;

        }
        
    }
}