# Exam Project

## Ideea
1. Add options to already existing website
2. Add version control for notes (1)
3. Add admins, able to do whathever they want (2)
4. Add Twitter-like messages (3)


### (1)
    1. Basic command for generating a graph is
        `dot -Tpng graph1.gv -o graph1.png -Gsize=9,15\!`
    2. Each note stores a history (each version has a parent
        except for the root one)
    3. Each note has an additional button with 'history', which opens:
        a. A list with all the versions, which can then be edited thus creating a new version
        b. A graph with the versions history (generated using the command above from the server)
    4. Even the deleted notes aren't really deleted, they can still be accessed from the "deleted notes" menu, and be restored.


### (2)
    1. Each admin can only be created by editing server config files.
    2. When an admin sign-in it basically creates an universal token.
    3. Any request with an admin token is accepted.
    4. As all is single-page, the admin can:
        a. Sign-in as another person
        b. has a button on the top of the screen for going back

### (3)
    1. Each user can create a new message that will be published publicly.
    2. A user or an admin can edit his own messages.
    3. A guest can only see messages
    Usefull links: (this)[https://www.w3schools.com/howto/howto_js_popup_chat.asp] and (this)[https://www.w3schools.com/howto/howto_css_chat.asp]

# Nota: toate taskurile trebuie sa fie integrate cu sens in aplicatie. Cautati in lista un task care sa se potriveasca tipului vostru de proiect. Se pot alege in total maxim 5 taskuri din toate categoriile. Punctajul obtinut este reprezentat de suma punctajelor pe taskuri, in cazul in care depaseste 6 puncte, suma fiind trunchiata la 6. Nu pot exista doi studenti cu cod similar la acelasi task (se anuleaza tot punctajul). Fiecare student se va consulta cu profesorul de laborator, si sa ajunga la comun acord cu studentul referitor la alegerea setului de taskuri. 
Ne rezervam dreptul de a adauga variante noi de taskuri pentru a fi alese de studenti.
 

## II) Taskuri de nivel 2 (punctaj: 0.5p):
 
Varsta utilizator. Va exista in pagina, la inceput, un input in care un utilizator isi poate trece data nasterii sub forma zi#luna#an. La click pe un buton se va afisa imediat sub input varsta utilizatoului in ani, luni si zile ( de exemplu: 19 ani 3 luni si 4 zile)

Timp petrecut pe pagina. Folosind localStorage sa se afiseze pe fiecare pagina (de exemplu in footer) numarul de minute si secunde petrecute de un utilizator pe pagina curenta (se va afisa pe fiecare pagina a site-ului. Realizati taskul folosind aceeasi functie pentru toate paginile.

Schimbarea dinamica a unui formular in functie de inputul utilizatorului. Sa se schimbe in mod dinamic un formular (adaugand sau stergand, pe masura ce e completat (de exemplu, in cadrul unui formular avem un camp de tip select cu nivelul de invatamant la care a ajuns utilizatorul. Daca alege liceu sa apara doua inputuri text care cer scoala generala si liceul urmate, iar daca alege facultate sa apara si un input pentru facultate). Sau pentru un formular de comanda, avem un checkbox cu "livrare la domiciliu" si la bifarea lui apare un camp pentru adresa (care dispare la debifarea checkboxului)

Prevenirea evenimentelor default (Exemple: la click dreapta sa nu mai apara submeniul ci sa se petreaca alta actiune definita de student; la click pe un link sa nu se deschida (sau nu imediat ci facand verificari, de exemplu daca utilizatorul are drept de accesare a acelui link) , sa se dea alte semnificatii unor combinatii de taste aflate printre shortcuturile browserului precum ctr+s etc.

### Intrebare in timp limita. Pentru o pagina cu mai mult text, presupunem ca avem la final o intrebare referitoare la continutul textului, un input de tip text si un buton. Din momentul in care utilizatorul se focuseaza pe input, daca trec mai mult  de 3 secunde si nu a facut inca click pe buton, se va dezactiva inputul si se va da un alert cu mesajul "Timpul a expirat!". Daca a facut click pe buton inainte de sa expire timpul, va primi un alert cu "Felicitari!", altfel un mesaj cu "Ai gresit!"

Salut, utilizator! La intrarea pe pagina se va afisa un prompt cu intrebarea, "Cum te numesti?" Dupa ce utilizatorul raspunde, title-ul tab-ului se va schimba in "Salut, nume!", ramand astfel 2 secunde si apoi revenind la valoarea initiala.

Numar cuvinte. Sa se afiseze la finalul fiecarei paginii din site, in footer, numarul de cuvinte existente in body (consideram cuvintele ca fiind separate prin spatii.
 
 
## III) Taskuri de nivel 3 (punctaj: 1p):

### Sa se genereze un quiz cu raspunsuri corecte multiple (legat de continutul site-ului) stil test grila pe baza unui vector de obiecte (gasit in fisierul javascript). Obiectele vor fi de forma: {intrebare:"Text intrebare", raspunsuri:[["r1", true], ["r2", false], ["r3", true],["r4", false]]}. Pot fi oricate raspunsuri pentru o intrebare. Raspunsurile sunt puse intr-o lista. fiecare raspuns are de asemenea asociata o lista de doua elemente: un sir cu textul raspunsului si un boolean prin care se indica daca raspunsul e corect (true) sau nu (false). Se va genera (dinamic, prin JS) in pagina acest quiz, sub forma unei liste ordonate, unde fiecare intrebare e un list item. Raspunsurile vor fi ilustrate prin checkbox-uri. Se va genera dinamic si un buton, care la click va realiza evaluarea raspunsurilor (verificand daca checkboxurile bifate corespund raspunsurilor corecte). Clickul pe buton va avea ca rezultat dezactivarea checkboxurilor(nu mai pot fi modificate) si afisarea scorului sub buton.

Afisarea ip-ului si timpului de la ultima logare pentru utilizatorul logat, cat si numarul de vizitari (de exemplu:"Salut, Gheorghe, ultima oara ai intrat de pe ip-ul 109.123.88.44 in ziua 23.04.2020 la ora 17:55:22. Ai vizitat site-ul de 215 ori"). In cazul in care utilizatorul se logheaza pentru prima oara, primeste mesajul "Salut, te-ai logat azi pentru prima oara".

Realizarea unui event log pe pagina. La click pe un buton se va afisa un div in care sunt consemnate evenimentele(de mouse si tastatura) realizate de un utilizator de cand a intrat pe pagina (se vor memora minim 4 tipuri de evenimente). Formatul de afisare va fi (orele minute si secundele se vor scrie cu 0 in fata daca sunt <10):
"an/luna/zi hh:mm:ss tip eveniment, date eveniment", de exemplu:
"2020/05/01 20:32:17 keydown, tasta y"
"2020/05/01 20:32:17 dblclick, coord 143, 220"

(joc) Crearea unei pagini de highscores pentru un joc (Node). Pagina de highscores se va pastra intre sesiuni (se va salva intr-un fisier). Pentru fiecare scor se vor pastra urmatoarele informatii: utilizator,scor, data obtinerii. Va avea optiunea de reset, respectiv de stergere a scorurilor unui anumit jucator. 

Realizarea unui captcha (atentie, doar conform modului precizat mai jos). In cadrul unui formular va exista si un camp pentru captcha si deasupra lui un div in care se genereaza aleator caractere. Caracterele vor fi la pozitii diferite dar fara a se intersecta pe orizontala (adica nu apare un caracter sub un alt caracter ci doar in lateral, chiar daca la coordonate y diferite). Caracterele pot fi cifre, litere mici si litere mari Pe caracterele respective se aplica aleator atat transformari de tip rotate, cat si skew, se aplica culori diferite aleatoare, caracterele vor fi de dimensiuni aleatoare, si din font-family-uri aleatoare. Va exista un buton cu "creeaza alt captcha" care va genera alte litere stilizate in alt mod aleator. Utilizatorul trebuie sa completeze campul de sub captcha cu exact caracterele generate in div. In cazul in care se da submit fara captcha corect comepletat, utilizatorul primeste o alerta cu mesajul "Captcha gresit!" si automat se genereaza alt captcha.

### Codul Morse (https://en.wikipedia.org/wiki/Morse_code). Intr-un camp de pe site (de exemplu, un textarea) utilizatorul poate completa, folosind codul morse. Clickuri rapide pe textarea ar insemna semnale scurte (se face mousedown si imediat mouse up, tipul intre cele doua evenimente trebuie sa fie sub 1 secunda). Un semna lung ar insemna o pauza intre 1 si 3 secunde intre mousedown si mouseup. In cazul in care pauza depaseste 3 secunde se ignora semnalul. Dupa ce s-au generat suficiente semnale cat sa se afiseze un caracter, acesta apare in textarea. Textarea-ul nu poate fi modificat prin apasare de caractere chiar daca utilizatorul e focusat pe el. Textarea-ul va avea si un buton de reset care va sterge continutul, un buton prin care poate sa ignore ultimele semnale de la scrierea unui caracter in text area (practic urmatorul semnal marcheaza inceputul identificarii unei litere noi), dar si un buton de stergere a ultimului caracter.

## IV) Taskuri de nivel 4 (punctaj 1.5p) :
 
### (Node) Sugestii cautare pagina. La incercarea de a accesa un link invalid (gresit), cand se afiseaza pagina de eroare 404, se vor afisa, daca e cazul, si niste sugestii (in format de link) in stilul:  "Ai vrut sa scrii: varianta1, varianta2 etc". Sugestiile se vor face in felul urmator: pornind de la cererea de pagina se vor cauta in views toate paginile al caror nume seamana cu numele cererii (pentru acest task se pot face cateva pagini cu nume asemanator astfel incat sa existe minim 2 cereri pentru care sa fie afisate minim 2 sugestii. Numele sunt considerate asemanatoare, daca au o litera in plus sau in minus, sau o litera din sir e schimbata.

(Node) Crearea unei pagini in care utilizatorii pot lasa comentarii (prin intermediul unui formular). Pagina va avea si o optiune de a ascunde/afisa comentariile. Comentariile pot primi voturi pozitive sau negative (vor exista doua butoane cu simbolurile + si -). Un comentariu cu prea multe voturi negative (de exemplu, peste 3) nu mai e afisat.

V) Taskuri de nivel 5 (punctaj  2p): 

Utilizatori cu roluri diferite: admin, user obisnuit, guest. Rolurile inseamna drepturi diferite de acces si modificare a datelor din site:
adminul poate avea cces la pagini ascunse pentru utilizatorii obisnuiti, poate realiza actiuni asupra utilizatorilor: adaugare, stergere, blocare, resetare parola pentru diversi utilizatori, dar poate face si tot ce face un utilizator obisnuit
utilizatorul obisnuit poate realiza diverse alte actiuni asupra datelor din site: de exemplu sa isi schimbe profilul, sa adauge un comentariu, sa dea un rating etc. Poate accesa pagini dedicate doar utilizatorilor inregistrati (de exemplu sa vizualizeze pagina in care sunt afisate numele celorlalti utilizatori)
guest e utilizatorul nelogat, care practic are doar drepturi de vizualizare (nu poate modifica nimic in cadrul site-ului), in plus nu va avea acces la anumite pagini.
 
### (Node) Sa se realizeze operatia de logging (memorarea intr-un fisier in format ales de studenti a actiunilor importante (in special de modificare a datelor din site) facute de utilizatori (trebuie minim 4 tipuri de actiuni: de exemplu vizualizare, adaugare, stergere, modificare). Intr-un camp al fisierului de log ar trebui memorate: numele utilizatorului, data si ora la care s-a petrecut actiunea, informatii despre actiune (de exemplu, "[10/02/2020, 08:34:25] ]utilizatorul ion.popescu a sters produsul 2345 din baza de date.")
 
Afisarea utilizatorilor online, cu actulizare dinamica atunci cand cineva se delogheaza. Lista de utilizatori online se va vedea pe fiecare pagina (fiind inclusa prin intermediul unui template). Pentru fiecare utilizator va fi scris in paranteza de cata vreme e logat. Se considera un utilizator online daca s-a logat in urma cu mai putin de 5 minute, si nu a efectuat manual operatia de logout). In momentul in care in utilizator se delogheaza, evenimentul este transmis catre toti utilizatorii conectati, si utilizatorul delogat dispare din lista utilizatorilor activi.
 
Posibilitatea de a cauta in tot site-ul un cuvant, afisand sectiunile care il contin. Taskul se va realiza folosind Node. Va exista un searchbar in care utilizatorul scrie cuvantul. La click pe ok, se afiseaza linkuri cu target (pagina.html#target) catre sectiunile/articolele din site care contin acel cuvant. In dreptul fiecarul link se afiseaza in paranteza o fereastra de context a cuvantului cautat afisand 7 cuvinte din stanga si 7 cuvinte din dreapta din cadrul contextului cuvantului - daca aceste cuvinte exista. Cuvantul cautat va fi marcat cu o culoare de background, de exemplu verde deschis, pentru a-l observa usor in citatul oferit. Va exista un buton prin care se permite resetarea cautarii.
 
Sa se poata afisa istoricul activitatilor fiecarui utilizator: paginile vizitate din site (afisate sub forma de lista ordonata descrescator, dupa data ultimei vizitari, avand data respectiva in paranteza, in dreptul fiecarei pagini), articolele citite (afisate sub forma de lista neordonata), cat timp a petrecut pe fiecare pagina (afisaj tabelar cu doua coloane: pagina si timpul), datile in care s-a logat (ultimele 5, afisate ca lista ordonata crescator dupa date), linkurile externe pe care a dat click (afisate ca lista neordonata). Pentru fiecare utilizator va exista posibilitatea de a reseta datele (atat utilizatorul, cat si eventualul admin - in cazul in care s-au implementat roluri) va putea reseta activitatea.
 
Pentru un afisaj tabelar (de exemplu grid) , posibilitatea de a face operatiile  "merge" intre celule (unirea a doua celule intr-una singura) si resize cu mouse-ul (in stil similar excel-ului). De exemplu se pot selecta doua celule cu ctrl/alt/shift+click si apoi sa se apese pe o tasta, de exemplu, "M" pentru unirea celor doua celule. Pentru resize, se poate folosi chiar proprietatea CSS resize, care sa fie activata/dezactivata in urma unui click pe buton sau a unei combinatii de taste.
 
Interactiune intre utilizatorii logati. Minim un tip de interactiune dintre cele descrise mai jos:
utilizatorii isi pot trimite mesaje (in momentul in care utilizatorul primeste un mesaj de la alt utilizator logat, este notificat si poate vizualiza mesajul. Utilizatorul va avea un fel de inbox cu toate mesajele primite. Pentru fiecare mesaje are un buton de stergere (nu se va mai afisa in pagina dar se va sterge si din date) si un buton de reply.
crearea de relatii intre utilizatori. Utilizatorii se pot adauga drept prieteni (un utilizator trimite o cerere si celalalt o accepta), moment in care isi pot trimite niste mesaje standard de tip emoji, fara a fi personalizate: "salut", "pa pa", "succes!", "zi frumoasa" etc exprimate prin niste imagini standard oferite de site. Daca nu sunt prieteni, nu isi pot trimite imaginile. Evident, utilizatorii se si pot desprieteni sau chiar bloca (un utilizator nu mai permite altui utilizator sa ii trimita cereri de prietenie).
utilizatorii pot juca un joc cu miscari real-time: de exemplu fiecare vede pozitia actualizata a celuilalt pe o harta, sau un utilizator vede mutarile celuilalt utilizator pe o tabla de joc stil board game (dar pentru joc cerintele se iau obligatoriu de la profesorul de laborator).
 
Posibilitatea ca utilizatorii sa isi faca pagini proprii in site. Va exista un editor, sub forma de formular in care vor scrie:  un cod CSS activ pentru pagina lor,  titlul si continutul paginii care poate fi in format html (in formular). Formularul va avea si niste butoane pentru tagurile uzuale (paragraf, bold, italic etc). La click pe un astfel de buton, in pozitia cursorului, se insereaza tagurile de deschidere si inchidere pentru acel element. Pagina va primi un nume care sa fie format din numele utilizatorului si titlul dat. Paginile astfel create vor aparea in meniul site-ului (doar pentru utilizatorul logat) ca suboptiuni pentru optiunea principala din meniu, "Pagini proprii".
 
Verificarea incercarilor de login esuate. In cazul in care se incearca logarea pentru un anumit user si se finalizeaza cu esec de un numar N de ori (de exemplu N=5) intr-un interval de 3 minute, se va bloca login-ul pentru un interval scurt (exemplu: 5 secunde - ca sa fie usor de prezentat la momentul evaluarii). Dupa fiecare incercare esuata de login se va scrie in pagina cate incercari mai sunt pana la blocarea contului. La a N-a incercare se va trimite si un mail catre utilizatorul detinator al contului, in care sa fie alertat.

Posibilitatea unui utilizator de a pune un bookmark oriunde in pagina. Acest lucru s-ar petrece in felul urmator: utilizatorul ar da click apasand in acelasi timp si o tasta. In acel loc (pozitionare absoluta) s-ar crea un element transparent (opacitate 0.3-0.5) pe care scrie "bookmark nr_de_ordine" (numarul de ordine creste la fiecare bookmark nou al utilizatorului). La dublu-click pe el s-ar afisa un prompt in care utilizatorul poate sa scrie un nume pentru bookmark. Pentru utilizatorii care au creat bookmarks, ar aparea o optiune in plus in meniul principal, care va avea drept submeniu, bookmarkurile astfel create. La click pe ele utilizatorul este dus exact in pozitia bookmarkului. Bookmarkurile trebuie sa aiba posibilitatea de a fi mutate, editate sau sterse.

Identificarea cuvintelor cheie din sectiuni pe baza frecventei si crearea unui "tag cloud" cu cuvintele ordonate dupa relevanta. cuvintele cheie vor fi considerate doar pasajele din taguri b. Tag cloud-ul va avea urmatorul format: se va afisa la inceputul fiecarei sectiuni sub forma unei liste sau a unor cuvinte enumerate cu virgula. In dreptul fiecarui cuvant, in paranteza este scris de cate ori apare cuvantul in text (nu doar in elemente de tip b. De exemplu, daca apare de 3 ori in elemente b dar de 5 ori in afara tagurilor b, se va afisa 8). La click pe oricare dintre aceste cuvinte din tag cloud, acestea vor fi marcate in text, cu un background diferit. La click din nou pe un alt cuvant, se dezactiveaza marcajele vechi si se activeaza marcajele noului cuvant. La click pe cuvantul cu marcajele active, se dezactiveaza marcajele.
 
Cautarea unor imagini in pagina dupa anumite cuvinte cheie. Cautarea trebuie sa se realizeze pe o pagina cu mai multe imagini (minim 10) cu atributele alt si title continand texte descriptive pentru imagini. In pagina va exista un formular cu urmatoarele elemente:
trei campuri text fiecare urmate de un grup de doua radio buttons. Campurile text vor fi: alt, title, context. In fiecare camp text se pot scrie mai multe cuvinte separate prin virgula. Cuvintele trecute in campurile alt si title se vor cauta in valorile atributelor alt si title ale imaginii. Cuvintele din context se vor cauta in textul vecin imaginii (pentru simplitate consideram textul din acelasi container cu imaginea, de exemplu pentru "text_inainte <img..> text_dupa" se considera ambele texte, dar pentru  "text_inainte <p><img..> text_dupa</p>" se considera doar text_dupa. Cele doua radiobuttons care urmeaza fiecare camp de tip text au valorile "si", respectiv "sau" (la bifarea lui "si" trebuie sa existe toate cuvintele in zona corespunzatoare campului; la bifarea lui "sau" trebuie macar unul sa existe)
un buton pe care se da click si care cauta imaginile care indeplinesc conditiile din formular. Imaginile se vor afisa sub formular(nu vor fi mutate ci clonate (cloneNode)).
un buton de resetare a cautarii (va goli campurile, va debifa radiobutton-urile si va sterge imaginile din cautarea anterioara)
 
VI) Taskuri de nivel 6 (punctaj  2.5p): 
 
Sistem de versionare pentru notite. Va exista o pagina speciala, numita "notite". In ea va fi un camp editabil in care utilizatorul logat poate sa scrie ceva (daca nu e logat, se va afisa un mesaj de atentionare pe pagina, si nu va fi afisat campul editabil). La click pe butonul save textul se salveaza intr-un fisier, folosind Node. Fiecare salvare va genera o noua versiune (un nou fisier). Pentru salvarea fisierelor, se va crea un folder(daca nu exista deja) cu numele utilizatorului, iar in cadrul acestui folder se va mai face un folder numit notite. Fisierele pentru notite se vor salva in formatul notite_nrOrdine.txt, unde nrOrdine e un numar de ordine. Va exista in pagina un buton numit "afiseaza versiuni" care va face o cerere AJAX catre server, si va primi lista de fisiere de tip notite, din folder, impreuna cu data crearii. Se va afisa in pagina aceasta lista in formatul urmator: [nume_fisier, data_creare, timp_creare], de exemplu [notite_1234.txt, 04.05.2020, 20:35:21]. Lista va fi ordonata descrescator dupa data (de la cel mai recent la cel mai vechi). Utilizatorul poate alege un fisier dintre cele din lista si continutul acelui fisier (versiunea anterioara) va fi afisat in campul editabil pentru notite, utilizatorul putand continua modificarea de acolo (totusi la urmatorul save, se va ignora faptul ca s-a pornit de la o versiune mai veche si doar se va salva o versiune cu un numar de ordine mai mare).

Afisarea "grafului" de linkuri ale site-ului (sitemap-ul). Prin node se va verifica care sunt linkurile catre care "pointeaza" fiecare pagina. Se va genera prin node o pagina, numita "graf site", unde pentru fiecare pagina din site cu linkuri fixe (scrise in fisierele din views si nu incluse dinamic) se va crea o lista cu linkurile catre alte pagini (asemanator unui sitemap).
 
Calcularea unor statistici si grafice pe baza actiunilor utilizatorilor ( actiunile urmarite pot fi: linkurile pe care a dat click, sectiunile pe care le-a citit (la care a ajuns cu scroll-ul), timpul petrecut pe o pagina). Statisticile se vor afisa pe o pagina speciala dedicata lor,  sub forma de grafic in felul urmator: de exemplu, pentru fiecare pagina se poate afisa, care sunt sectiunile cele mai citite, timpul minim, maxim si mediu petrecut pe acea pagina de catre utilizatori, numarul clickuri pe linkurile de pe acea pagina. Graficul poate sa fie in felul urmator: pentru fiecare pagina, se vor afisa 7 divuri corespunzatoare  ultimelor 7 zile, inaltimea fiecarui div va arata cat de vizitata a fost pagina respectiva (numarul de intrari sau timpul total petrecut pe ea). Inaltimea divurilor ar trebui scalata de asa natura incat sa reprezinte un procentaj (sa nu fie prea inalte in pagina).

Crearea unui calendar de evenimente (evenimentele se vor salva intr-un json sau baza de date), evenimentele pot sa fie pentru un utilizator(logat) sau pentru toti utilizatorii. Va avea o interfata in care se pot afisa pe rand zilele din fiecare luna. La dubluclick pe o zi se va afisa un formular sub calendar cu campurile: titlu, descriere si prioritate (prin care s-ar descrie evenimentul sia poi s-ar salva la submit). Prioritatile ar fi de 3 feluri (rosu - foarte important, galben - important, verde - obisnuit). Zilele cu evenimente ar fi marcate cu culoarea respectiva, iar cand se vine cu cursorul pe o zi marcata, se afiseaza in dreptul cursorului titlul si descrierea evenimentului. 
 
VII) Taskuri de nivel 7 (punctaj  3p): 
 
Album de poze. Un utilizator logat poate avea optiunea de a uploada poze pe server pentru a-si crea un album. Va exista o pagina speciala, numita upload_poze cu un formular pentru upload-ul pozelor. Formularul va contine urmatoarele campuri:
nume (un input de tip text pentru numele pozei, care nu va permite decat caractere alfanumerice)
descriere (un textarea pentru descrierea pozei)
album (un input de tip text)
un camp de tip file pentru uploadarea pozei
un set de checkboxuri cu niste taguri posibile (prin tag ma refer la un cuvant cheie general care ar putea descrie poza, de exemplu: mare, munte, oras, relaxare, aglomeratie etc). Tagurile sunt predefinite
Deoarece nu s-a predat in mod explicit lucurul cu baze de date solutia propusa se va baza pe fisiere text. Pentru fiecare utilizator, se va crea, daca nu exista deja, un folder cu numele sau. In acest folder se va crea un alt folder cu numele "poze" in care se va salva la fiecare upload, poza si un fisier cu detaliile ei (fisierul cu detalii va avea numele de forma nume_poza_detalii.txt). Va exista o alta pagina numita poze, in care se pot vizualiza pozele. Pentru a vizualiza pozele, trebuie selectat albumul din care fac parte. Lista de albume se obtine printr-o cerere AJAX si se afiseaza la incarcarea paginii intr-un select. La alegerea unui album din select se afiseaza imaginile din acel album, in elemente de tip figure create printr-un template EJS impreuna cu detaliile lor puse in elemente DOM din figcaption. Imaginile vor avea si un buton de ascundere(la click pe el, dispar din pagina).
 
Se va implementa o functionalitate stil twitter. Utilizatorul va avea o pagina in care poate posta mesaje scurte (cu diverse tematici). Cererea pentru pagina va avea forma /mesaje?user=username. Cand pagina e vazuta de alti utilizatori, se afiseaza mesajele fara drept de editare. Mesajele se afiseaza cu titlu, text, o imagine de stare si data crearii. Cand pagina e vazuta de utilizatorul proprietar, mesajele deja existente au un buton de stergere in dreptul lor (stergerea se efectueaza in pagina, dar si pe server). In plus, va avea la inceputul paginii un formular de adaugare de mesaje noi care va contine campurile:
nume (input de tip text)
text mesaj (textarea)
un grup de radiobuttons cu imagini asociate in label, reprezentand starea exprimata de mesaj (suparat, vesel, plictisit etc.)
La submit se vor transmite informatiile spre server si acesta le va salva intr-un fisier dintr-un folder dedicat utilizatorului (folderul poate purta chiar numele utilizatorului).
 
(Node) Implementarea unui chat in Node conform cerintelor date. Va exista un box mare in care se afiseaza mesajele, iar dedesubt un formular prin care utilizatorul poate transmite propriile sale mesaje. Mesajele fiecarui utilizator se vor afisa cu o culoare si cu un timestamp (cand a transmis mesajul). In formularul de transmitere a mesajelor, utilizatorul poate selecta o culoare dintr-un input de tip color. La selectarea culorii, toate mesajele lui deja trimise capata acea culoare, atat pe ecranul lui cat si al celorlalti utilizatori, si toate mesajele trimise de acum inainte vor fi afisate cu acea culoare. Utilizatorul poate scrie un text intr-un box care simuleaza un input, dar poate insera si imagini de tip emoticon in text. Pentru asta va avea un set de 5 imagini stil smiley, pe care poate da click (moment in care apare imaginea si in boxul cu mesajul). La submit mesajul apare atat in chenarul sau de mesaje cat si pe ecranele celorlalti utilizatori, cu tot cu eventualele imagini. chatul nu va permite inserarea de cod html de catre utilizator (daca, de exemplu, utilizatorul scrie tagul <b> se afiseaza ca atare cu semnele < si > fara a fi transformat in text bold). Utilizatorii vor primi o notificare in cazul in care apare un utilizator nou in chat, sau se delogheaza. Va exista si un buton care permite afisarea utilizatorilor conectati.
 

