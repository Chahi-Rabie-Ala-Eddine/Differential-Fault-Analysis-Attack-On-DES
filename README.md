# Differential-fault-analysis-on-DES

CHAHI, Rabie Ala-Eddine
rabie_chahi@yahoo.fr
Numéro étudiant 21505593
Site web personnel
lien du projet Github
Master : SeCReT
Enseignant : Mr Goubin Louis

```
30 Avril 2020
```

# Abstract

L’association du hardware et du software bas niveau ouvre la porte
à des vulnérabilités sur l’ensemble et permet aux attaquants d’accéder
aux noyaux des programmes en passant les frontières matérielles à l’aide
d’attaques dites physiques. Ces attaques sont découpées principalement
en deux grandes classes les attaques par canaux auxiliaires analysant les
fuites physiques de l’implémentation matérielle du code et les attaques
par injection de fautes qui elles se traduisent par la perturbation du
fonctionnement des circuits. Nous nous intéresserons dans ce projet à
cette deuxième classe.

Pour réussir une telle attaque, il faut disposer du matériel nécessaire
et pouvoir affecter son état interne; il est également important d’être en
mesure de comprendre parfaitement le déroulement de chaque étape des
processus de chiffrement/déchiffrement de l’algorithme cryptographique
lié au programme; cette étape peut parfois prendre plusieurs semaines
voir plusieurs mois. Une fois l’algorithme maîtrisé, l’attaquant cherchera
à produire volontairement des erreurs dans le cryptosystème. L’effet
souhaité par cette injection est le comportement inhabituel des opéra-
tions cryptographiques. Si l’attaque est correctement réalisé l’attaquant
pourra extraire des informations secrètes telle que la clé utilisée. On
retrouve parfois certains procédé en cryptanalyse mêlant une attaque
par faute à d’autres attaques telle qu’une timing attack. Ces attaques
peuvent porter sur différents composants matériels tels que le crypto-
processeur, les logiciels, etc.

Nous aborderons dans le présent document, les détails d’une attaque par
injection de fautes sur l’algorithme Data Encryption Standard (DES).
Pour ce faire, nous réaliserons une attaque interprétable par un exé-
cutable fourni avec ce même document ainsi que les sources nécessaires
à la compilation. Nous supposerons avoir en notre possession un couple
formé d’un clair et d’un chiffré correct, ainsi que de trente-deux autres
couples formés à chaque fois de ce même message clair et d’un chiffré
erroné produit à l’aide de diverses injections de fautes. Notez que ce
document est consultable en ligne ici..


## Sommaire


- 1 Attaque par faute sur le DES
- 2 Application concrète
   - 2.1 Description précise de l’attaque
      - 2.1.1 Description théorique détaillé
      - 2.1.2 Attaque pratique
      - 2.1.3 Algorithme
   - 2.2 les 48 bits de clé obtenu
- 3 Retrouver la clé complète du DES
   - 3.1 Méthode pour trouver la cléK
      - 3.1.1 Trouver les bits manquants
      - 3.1.2 Calculs des bits de parité :
      - 3.1.3 Algorithme
   - 3.2 Les 64 bits de clé obtenu
- 4 Fautes sur les tours précédents
   - 4.1 Faute provoquée sur le 14 emetour
   - 4.2 Faute provoquée sur les autres tours
- 5 Contre mesures
- 6 Compilation et éxecutions


## 1 Attaque par faute sur le DES

Data Encryption Standard est un algorithme de chiffrement à clé secrète succé-
dant à l’algorithme Lucifer et développé par IBM 15 Janvier 1977, DES est un
chiffrement par bloc de 64 bits basé sur un shéma feistel à 16 tours. La clé initiale
fait 64 bits, seulement 56 d’entre eux sont effectivement utilisés par l’algorithme;
en effet huit bits sont utilisés uniquement pour le contrôle de la parité. Ces 56
bits sont par la suite transformés en 16 sous clés à travers le Key Schedule. Ces
dernières serviront à chiffrer les 2 parties du messages à travers les 16 tours.^1

Qu’est ce qu’une attaque par Faute sur DES?

Une attaque par fautes sur le Data Encryption Standard consiste à perturber
plusieurs fois le processus de chiffrement en injectant des fautes dans le but
d’obtenir la clé de chiffrement. Plus concrètement l’attaquant intervertit cer-
tains bits de la partie droiteRidu chiffré à la sortie d’un tour choisi parmis ceux
qui permettent un procédé calculatoirement faisable^2 , tel que le 15 eme tour du
Feistel, et ce, un certains nombre de fois, afin d’obtenir plusieurs chiffrés faux à
l’aide du même message clair et de la même clé de chiffrement.

L’attaquant peut choisir la position de la faute ainsi que le nombre de bit con-
cernés. Il y’a par définition deux modèles d’erreurs :

- Le single bit flip: un et un seul bit deR 15 est inversé parmis les 32.
- Le single byte flip: un octet deR 15 est inversé parmis les4 (32 = 4×8).

Une fois l’injection de fautes effectuée, l’attaquant dispose du message clair, de
son chiffré correct et d’un ensemble de messages chiffrés^3. Tous les chiffrés sont
obtenus en utilisant la même clé de chiffrement de 64 bits que l’attaquant à
pour objectif de déterminer. On considérera également que l’attaquant maîtrise
suffisement les différents processus lié au DES et qu’il est capable de chiffrer et
de déchiffrer librement des messages avec le DES^4.

(^1) Pour plus d’informations, un document est joint détaillant l’algorithme du DES.
(^2) Nous désignerons dans la partie 4 les tours possibles.
(^3) 32 dans le cas du one bit flip.
(^4) Dan notre cas nous avons à disposition un programme implémentant le DES.


L’attaquant ne disposant pas de la clé, la seule manière de péntrer le feistel est
d’utiliser les sorties^5 du DES que l’attaquant possède. Il connait la construction
interne du DES et de la fonctionf, il se servira donc des messages qu’il a en sa
possession pour inverser les opérations liées au chiffrement entre la sortie et le
15 emetour afin de remonter la 16 emesous clé K 16. Chaque chiffré faux apporte de
l’information sur un certain nombre de bits de la clé. En effet nous verrons par la
suite que chaque boîte S est concernée par un nombre précis de message, celà est
dû au simple bit flip surR 15 qui par construction infecte l’entrée d’au plus 2 S-Box.

Une fois K 16 obtenue, une analyse du key schedule et des positions des 8 bits
perdus lors du passage de 56 bits de clés à 48 bits^6 , permettra à l’attaquant de
remonter ces derniers. L’attaquant aura en sa possession à la fin de cette étape
une clé de 64 bits dont le 8 emebit^7 de chaque octet est potentiellement erroné.

Finlament, l’attaquant n’aura plus qu’a calculer les 8 bits de parités en met-
tant le bit à 0 si l’octet a un nombre impair de 1 et inversement. À la fin de cette
étape l’attaquant obtient une clé de 64 bits et procède à un test de cette dernière
en chiffrant avec le message clair.

Si la sortie du chiffrement correspond au chiffré correct, la clé est donc bel et bien
K 64 et l’attaque est terminée.

Cette attaque est beaucoup plus puissante et beaucoup moins coûteuse que des
attaques classique tel qu’une attaque par force brut de complexité 256 opérations
ou encore l’attaque par recherche exhaustive avec complément bit à bit de com-
plexité 254 opérations. la complexité de l’attaque par fautes sera calculée dans la
prochaine partie.

Ce qui précède est une ébauche théorique de l’attaque, nous détaillerons dans les
prochaines sections la méthode pratique à utiliser pour retrouver la clé de chiffre-
ment. Pour ce faire nous avons écrit un programme en C++, réalisant l’attaque et
montrant son déroulement à travers une animation^8.

(^5) Les différents chiffrés obtenus précédemment
(^6) On analysera les différentes tables de permutations du DES.
(^7) Bit de parité
(^8) Les détails pour la compilation et l’éxécution sont décrits dans le README joint.


## 2 Application concrète

### 2.1 Description précise de l’attaque

#### 2.1.1 Description théorique détaillé

Comme décrit dans la section précédente nous devons commencer par déterminer
K 16 afin de remonter la clé de chiffrement initiale.

Pour ce faire nous allons suivantes les étapes suivante :

1. Analyser la structure Feistel du DES :

```
Nous avons à chaque tour les équations suivantes :
```
```
Ri=Li− 1 ⊕f(Ri− 1 ,Ki)
Li=Ri− 1
```
```
L’injection de faute se fait sur le 15 emetour nous pouvons donc écrire :
```
```
Rc 16 =L 15 ⊕f(Rc 15 ,K 16 )
Lc 16 =Rc 15
```
```
De la même manière : ∀Rf 16 ∈L
```
```
Rf 16 =L 15 ⊕f(Rf 15 ,K 16 )
Lf 16 =Rf 15
```
```
Nous remarquons que K 16 et L 15 sont communs à Rc 16 et Rf 16 nous élim-
inerons donc lesL 15 de la manière suivante : ∀Rf 16 ∈L
```
```
Rc 16 ⊕Rf 16 = (L 15 ⊕f(Rc 15 ,K 16 ))⊕(L 15 ⊕(f(Rf 15 ,K 16 ))
```
```
Rc 16 ⊕Rf 16 = (L 15 ⊕L 15 )⊕(f(Rc 15 ,K 16 )⊕f(Rf 15 ,K 16 ))
Rc 16 ⊕Rf 16 =f(Rc 15 ,K 16 )⊕f(Rf 15 ,K 16 )
```

2. Analyser la fonctionf :

```
La fonctionfest la fonction interne du DES, elle prend en entrée une sous-clé
Ki et une partie droiteRi− 1. Elle calcule d’abbord l’expension deRi− 1 qui
passe de 32 à 48 bits et calcule esnuiteE(Ri− 1 )⊕Kiqui sera utilisé comme
entrée des 8 S-box.
L’entrée des S-boxs fait donc 48 bits^9 et donne en sortie 32 bits^10.
```
```
Nous pouvons donc écrire :
```
```
f(Ri− 1 ,Ki) =P(S(E(Ri− 1 )⊕Ki))
f(Ri− 1 ,Ki) =P(S 1 (E(Ri− 1 ⊕Ki)b 0 →b 5 )||...||...||S 8 (E(Ri− 1 ⊕Ki)b 43 →b 48 ))
```
```
Dans notre cas nous nous aurons : ∀Rf 16 ∈L
```
```
f(Rc 15 ,K 16 ) =P(S(E(Rc 15 ))⊕K 16 )
f(Rf 15 ,K 16 ) =P(S(E(Rf 15 )⊕K 16 ))
```
3. Parcours inverse de la fonction f :

```
Le but est de remonter jusqu’à K 16 qui se trouve en entrée de la S-Box
dans le calculE(R 15 )⊕K 16
```
```
D’après les formules précédentes : ∀Rf 16 ∈L
```
```
Rc 16 ⊕Rf 16 =f(Rc 15 ,K 16 )⊕f(Rf 15 ,K 16 )
```
```
Par conséquent : ∀R 16 f ∈L
```
```
Rc 16 ⊕Rf 16 =P(S(E(R 15 c )⊕K 16 ))⊕P(S(E(Rf 15 )⊕K 16 ))
```
```
P−^1 (Rc 16 ⊕Rf 16 ) =P−^1 (P(S(E(Rc 15 )⊕K 16 )))⊕P−^1 (P(S(E(R 15 f)⊕K 16 )))
```
```
P−^1 (Rc 16 ⊕Rf 16 ) =S(E(Rc 15 )⊕K 16 )⊕S(E(R 15 f)⊕K 16 )
```
(^9) 6 bits par S-Box
(^10) 4 bits par S-Box


4. Lier les messages chiffrés faux à la S-Box qu’ils infectent :

```
L’injection de faute est de type one bit flip^11 il y’a donc un seul bit er-
roné dans chaque Rf 15 ,. Il est donc important de remarquer qu’un chiffré
erroné ne fausse le résultat que de certaines S-Boxs.
```
```
En analysant la permutation d’expension, le bit erroné peut être ajouté ou
pas une seconde fois dans les 16 bits d’expensions; on en conclue donc qu’un
chiffré ne peut infecter que deux S-box au maximum. En conséquence de
quoi, nous déterminerons les messages infectants chaque S-box, et décom-
poserons donc nos messages en 8 listes. Chaque liste est donc lié à une S-box
en particulier ce qui convient à dire que chaque liste donne de l’information
sur les 4 bits de sortie de la S-box en question.
```
```
À la fin de cette étape nous chercherons à obtenir les 6 bits en entrée de
chaque S-Box séparément.
```
```
Rappelons que : ∀Rf 16 ∈L
```
```
P−^1 (Rc 16 ⊕Rf 16 ) désigne l’entrée des S-Box et qu’il est facilement calcula-
ble.
```
```
Plus concrètement : ∀R 16 f ∈L, pouri∈{ 1 ,..., 29 }etj∈{ 1 ,..., 8 }
```
```
P−^1 (Rc 16 ⊕Rf 16 )bi→bi+3=Sj(E(Rc 15 )⊕K 16 )bi→bi+3⊕Sj(E(Rf 15 )⊕K 16 )bi→bi+
```
5. Attaque exaustive sur K16 :

```
Après avoir généré les 264 12 mots de 6 bits, nous ferons une recherche ex-
austive sur la clé K16, en remplaçant donc à chaque fois K16 par l’un des 64
mots de 6 bits générés, et ce en calculant donc pour chacune des S-box et
pour chaque chiffré érroné lié à cette dernière :
```
```
Sj(E(Rc 15 )⊕K 16 )bi→bi+3⊕Sj(E(R 15 f)⊕K 16 )bi→bi+3 pouri∈ { 1 ,..., 29 }et
j∈{ 1 ,..., 8 }
```
(^11) Nous procéderons évidément à la vérification du type d’injection avant de commencer l’attaque.
(^12) Toutes les combinaisons possibles de 6 bits


```
Si ce calcul est équivalent à P−^1 (Rc 16 ⊕Rf 16 )bi→bi+3 pouri∈ { 1 ,..., 29 }et
j ∈ { 1 ,..., 8 } alors les 6 bits utlisé pour remplacerK 16 sont une partie^13
candidate pourK 16 , lié au chiffré faux sur lequel lequel le calcul est effectué.
```
```
Naturellement chaque chiffré faux de chaque S-Box addmet plusieurs solu-
tions candidates. À la fin de cette étape nous avons donc plusisuers solutions
de 6 bits lié à chaque chiffré faux de chaque S-box.
```
6. DéterminerK 16 :

```
Il nous suffira finalement de trouver dans un premier temps la solution com-
mune aux différentes solutions des chiffrés de chaque S-box afin de déterminer
les 8 partie de 6 bits de la sous-clé réelleK 16.
```
```
En concaténant dans l’ordre les 8 parties on aura un mot sur 48 bits qui
n’est autre que la sous-cléK 16
```
(^13) 6 bits


#### 2.1.2 Attaque pratique

Nous avons implémenté un programme en c++ permettant d’effectuer l’attaque.

Nous avons choisi de travailler en C++ en évitant les types complexes tel que
les bitset, les long etc, afin d’ajouter ce programme à un programme plus général
traitant des attaques par fautes. Nous utiliserons des strings tout au long de
l’implémentation.

Les fichiers utilisés :

- Concerter.cpp : contient un convertisseur pour gérer les différentes conver-
    sions (binaire - hexadécimal , binaire - décimal etc...)
- Utils.cpp : contient des méthodes gérant les opérations usuelles tels que le
    xor.
- Des.cpp : cotient une implémentation du DES.
- Analyzer.cc : contient les méthodes liées à l’analyse de l’injection de faute.
- Reverser.cpp : contient les méthodes liées à la pénétration inverse du DES.
- Attack.cpp : contient les méthodes responsables des différentes attaques de
    ce projet.
- Printer.cpp : contient les méthodes liées à l’animation de l’attaque.

Le fichier Attack.cpp contient la méthode attack48() qui va implémenter cette
attaque comme suit :

1. Annuler la permutationIP−^1 en effectuant simplement une permutationIP
    sur le chiffré correct.
2. Découper le message obtenu en 2 parties : Lc 16 etRc 16
3. ÉchangerLc 16 etRc 16 et stockerLc 16 dansRc 15
4. Calculer l’expansion deR 15
5. Mettre en relation les sbox et les chiffrés faux concernés


6. Générer les 64 mots de 6 bits possibles.
7. Pour chaque sbox

```
7.1. Pour chaque chiffré faux lié
i. Permutation IP sur le chiffré faux
ii. Découper le message obtenu en 2 parties : Lf 16 etRf 16
iii. ÉchangerLf 16 etRf 16 et stockerLf 16 dansRf 15
iv. Calculer l’expansion deRf 15
v. calculerRc 16 ⊕Rf 16
vi. calculer la valeur attendue des 4bits à la sortie de la S-box avec la
permutationP−^1 (Rc 16 ⊕Rf 16 )
vii. Pour chaque mot de 6 bits parmis les 64
A. Calcul de l’entrée de la sbox lié au chiffré correct
B. Calcul de l’entrée de la sbox lié au chiffré incorrect
C. Calul de la sortie de la sbox lié au chiffré correct
D. Calul de la sortie de la sbox lié au chiffré incorrect
E. Calcul du xor entre les deux sortie
F. Comparer le résultat et la valeur de vérification sur 4 bits
G. S’ils correspondent, stocker les 6 bits comme solutions valide pour
le chiffré en question.
viii. Ajouter la liste de solutions de ce chiffré au listes des autres chiffrés
infectants la S-Box actuelle.
```
8. Trouver les 8 solutions communes aux solutions des chiffrés de chaque S-Box
9. Concaténer les 8 solutions pour former un mot de 48 bits désignantK 16

Le code est entièrement commenté et permet donc de comprendre très facilement
l’implémentation.


#### 2.1.3 Algorithme

Algorithm 1Find SubkeyK 16
Input : plaintext, ciphertext, ciphers[ ]
Output : K 16
1: procedureFindK 16
2: correct←IP(ciphertext)
3: Rc 16 ←SplitTwoParts(correct[0])
4: Lc 16 ←SplitTwoParts(correct[1])
5: Swap(Rc 16 ,Lc 16 )
6: Rc 15 ←Lc 16
7: Expandedc←Expansion(Rc 15 )
8: links[ ]←Link(ciphers)
9: binaries[ ]←GenerateAttackKeys( 6 )
10: α← 0 β← 0 l← 0
11: fori∈{ 1 ,..., 8 }do
12: forj∈{ 1 ,..., 6 }do
13: incorrect←IP(ciphers[links[i][j]])
14: Rf 16 ←SplitTwoParts(correct[0])
15: Lf 16 ←SplitTwoParts(correct[1])
16: Swap(Rf 16 ,Lf 16 )
17: Rf 15 ←Lf 16
18: Expandedc←Expansion(Rf 15 )
19: xored←Xor(R 16 c,Rf 16 )
20: expected←UndoFFunctionPermutation(xored)
21: fork∈{ 1 ,..., 64 }do
22: inputc←Xor(Expandedcα→α+6,binaries[k])
23: inputf←Xor(Expandedfl→l+6,binaries[k])
24: outputc←GetSbox(inputc,i)
25: outputf←GetSbox(inputf,i)
26: result←Xor(outputc,outputf)
27: ifresult=expectedβ→β+4then
28: solutions[i][j][l]←binaries[k]
29: l← 0
30: α←α+ 6
31: β←β+ 4
32: parts[ ]←FindCommonSultion(solutions)
33: K 16 ←Concatenate(parts)
34: returnK 16

Complexité : La complexité criptographique de cet algorithme dépend de la
recherche exhaustive, les autres opérations se font en temps constant et sont donc
négligeables. Nous avons un total de 8 S-box et chaque est lié à 6 messages dif-
férents, chaque message opère une boucle de 26 tours, nous avons donc finalement
une complexité de 8 × 6 × 26 = 2^10 × 3 ≈ 212


### 2.2 les 48 bits de clé obtenu

La cléK 16 obtenu est F180096CF02.

Quelques passage de l’animation :

Traîtement des S-box 1 et 2 :

Détection de la solution en commun pour les S-box 1 et 2 :


Formation deK 16 :

K 16 en héxadécimal :


## 3 Retrouver la clé complète du DES

### 3.1 Méthode pour trouver la cléK

#### 3.1.1 Trouver les bits manquants

Dans ce qui précède nous avons réussi à retrouver la clé K 16 de 48 bits, il nous
faut retrouver les 8 bits manquants pour avoir les 56 bits de clé ainsi que les 8
bits de parités restants pour compléter la clé initiale de celle 64 bits.

Nous allons faire ceci en plusieurs étapes :

1. Analyse du la key schedule :

```
La clé initialeK 64 subit une première permutation et perd ses bits de parité,
la clé obtenu fait donc 56 bits, cette clé va être découpé en deux parties qui
subiront des shifts circulaires^14 avant d’être concaténer pour former la sous
clé du tour.
```
2. Conclusion du key schedule :

```
La première sous clé est correspondante à la dernière car la somme des shifts
circulaires donne 28 comme ceci :
n∑=
n=
```
```
shifti= 28
```
```
Ce qui correspond à la taille des deux blocs de chaque sous clé.
```
```
Il suffit donc d’effectuer les permutations inverses dePC 1 et PC 2 surK 16
pour avoir :
```
```
K 64 =PC 1 −^1 (PC 2 −^1 (K 16 ))
```
(^14) décallage d’une 1 ou 2 positions selon le numéro du tour


```
Seulement 8 bits sont perdus entreK 56 etK 16 il faudra donc déterminer la
position ces 8 bits à l’aide d’une recherche exaustive. En effet, le nombre
de tous les mots de 8 bits est 28 ce qui est largement calculable avec une
machine en 2020.
```
3. Déterminer les positions des bits manquants :

```
En analysant la permutationPC 2. nous avons pû déduire les positions des
bits manquants :
```
```
Positions des bits manquants^15 ={ 9 , 18 , 22 , 25 , 35 , 38 , 43 , 54 }
```
```
Nous appliquerons ensuite la permutationPC 1 c’est pouquoi nous devons
l’analyser également afin de déterminer la nouvelle position de ces bits.
```
```
Positions des bits manquants^16 ={ 14 , 15 , 19 , 20 , 51 , 54 , 58 , 60 }
```
4. Attaque par recherche exaustive sur les 8 bits manquants :

```
Nous calculons donc dans un premier temps PC 2 −^1 (K 16 ), nous obtenons
une clé de 56 bits dont les bits manquants sont mis à zéro. Nous calculerons
par la suitePC 1 −^1 (PC 2 −^1 (K 16 ))afin d’obtenir une clé sur 64 bits dont les
bits manquants ainsi que les bits de parité sont mis à 0.
```
```
Nous ferons par la suite une recherche exaustive sur toutes les combinaisons
possible de 8 bits générés préalablement, en testant à chaque fois les 8 bits
candidats en faisant un chiffrement DES sur le text clair donné en le com-
parant au chiffré correct, s’ils correspondent on arrête et on a trouvé les 56
bits de clé.
```
```
Notons que ceci est possible car les 8 bits de parité n’interviennent pas ni
dans le key schedule ni dans le chiffrement contrairement au 8 bits perdus.
```
(^15) AprèsP C 2
(^16) AprèsP C 1


#### 3.1.2 Calculs des bits de parité :

L’étape précédante nous a permis d’avoir une clé sur 64 bits dont le 8 emebit de
chaque octet désigngant le bit de parité est potentiellement érronné. Retrouver le
bit de parité d’origine est très simple, il suffit de mettre chaque 8ème bit de chaque
octet à 0 si ce dernier possède a un nombre impair de 1 et à 0 dans le cas contraire.

Nous devrons comme étape ultime vérifié le résultat de l’attaque en chiffrant
le message clair à l’aide deK 64 qu’on vient d’obtenir et de comparer le résultat
au chiffré correct. S’ils sont équivalent, la clé trouvé est bel bien la clé complète
du DES.

Cette attaque est implementé dans les deux méthodes attack56() et attack64()
dans le fichier attack.cpp.

#### 3.1.3 Algorithme

Algorithm 2Find keyK 64
Input : plaintext, ciphertext,K 16
Output : K 64
1: procedureFindK 64
2: binaries[ ]←GenerateAttackKeys( 8 )
3: K 56 ←PC 2 −^1 (K 16 )
4: K 64 ←PC 1 −^1 (K 56 )
5: fori∈{ 1 ,..., 256 }do
6: K 64 ←GetCandidate(K 64 ,binaries[u])
7: temp←DESK 64 (plaintext)
8: iftemp=ciphertextthen
9: K 64 ←temp
10: break
11: for(i= 0,i≤ 63 ,i+ = 8)do
12: K 64 ←ComputeParityBits(K 64 ,i)
13: ifDESK 64 (plaintext) 6 =ciphertextthen
14: Error(K 64 )
15: returnK 64


### 3.2 Les 64 bits de clé obtenu

La cléK 64 obtenu est 2C58400B195B802A.

Qulques étapes de l’animation :

Calculer les inverses dePC 1 etPC 2 :

Trouver les 56 bits de clé :

Calculer les bits de parité :


Vérifier la clé obtenu :


## 4 Fautes sur les tours précédents

Rappelons que la complexité de notre algorithme pour trouverK 16 à l’aide d’une
injection par faute sur le 15 emetour est d’envrions 212.

### 4.1 Faute provoquée sur le 14 emetour

On raisonnat de la même manière que précédement on obtient 2 équations :

R 15 c =Lc 14 ⊕f(Rc 14 ,K 15 )

Lc 15 =Rc 14

Mais aussi :

R 15 f =Lf 14 ⊕f(Rf 14 ,K 15 )

Lf 15 =Rf 14

Nous avons par conséquent :

R 15 c ⊕Rf 15 =Lc 14 ⊕f(Rc 14 ,K 15 )⊕Lf 14 ⊕f(Rf 14 ,K 15 )

Ce qui donne :

P−^1 (Rc 15 ⊕Rf 15 ) =Sk(E(Rc 14 )⊕K 15 )⊕Sk(E(R 14 f)⊕K 15 )

Par ailleurs :

R 14 c =Lc 15 =Rc 16 ⊕f(K 16 ,L 16 )⇔P−^1 (Lc 15 ⊕Rc 16 )i→j=Sk(E(Lc 16 )⊕K 16 )i→j

R 14 f =Lf 15 =Rf 16 ⊕f(K 16 ,Lf 16 )⇔P−^1 (Lf 15 ⊕Rf 16 )i→j=Sk(E(Lf 16 )⊕K 16 )i→j


Le but est de trouver K15, nous procéderons donc a une recheche exhaustive pour
déduire les possibleLc 15 etLf 15 en utilisant :

R 14 c =Lc 15 =Rc 16 ⊕f(K 16 ,L 16 )⇔P−^1 (Lc 15 ⊕Rc 16 )i→j=Sk(E(Lc 16 )⊕K 16 )i→j

R 14 f =Lf 15 =Rf 16 ⊕f(K 16 ,Lf 16 )⇔P−^1 (Lf 15 ⊕Rf 16 )i→j=Sk(E(Lf 16 )⊕K 16 )i→j

pour les utiliser dans une deuxième recherche exhaustive pour trouver K 15 en
utilisant :

P−^1 (Rc 15 ⊕Rf 15 ) =Sk(E(Rc 14 )⊕K 15 )⊕Sk(E(R 14 f)⊕K 15 ).

Le fait de remonter les équations de cette manière permet théoriquement de re-
monter le DES quelque soit le tour dans lequel les fautes sont injecté, quoique la
réalité est toute autre, nous verrons dans la suite les limites de cettes attaque.

Ces deux opérations sont de même complexité que la recherche exhaustive sur
K 16 donc la complexité d’attaque sur chaque tour implique de multiplier la com-
plexité de l’attaque surK 16 par la complexité du tour qui précède , la complexité
est donc élevé au carrée pour le 14 emetour et donne(2^12 )^2 = 2^24.

Rappelons que la lois de Moore indique qu’il est possiblé d’aller jusqu’à 280 dans
un contexte publique. Cette attaque est donc largement faisable.

### 4.2 Faute provoquée sur les autres tours

Comme dit plus haut cette attaque permet de remonter dans le DES quelque soit
le tour, seulement les capacités calculatoire étant limité à 280 et sachant que notre
attaque est élevé au carré à chaque tour nous avons donc les complexité suivante

- 15 emetour : 212
- 14 emetour : 224
- 13 emetour : 236
- 12 emetour : 248
- 11 emetour : 260


- 10 emetour : 272
- 9 emetour : 284

L’attaque est donc calculatoirement posssible jusqu’au 10 ème tour!

## 5 Contre mesures

Voici une liste de contre mesure empéchant l’attaque par faute sur le Des :

- Déchiffrer le message obtenu à l’aide de la clé avant de retourner le résultat
    pour vérifier s’il s’agit du bon chiffré. Dans le cas contraire aucun résultat
    ne devrai être retourné après un certains nombre de calcul. Cette méth-
    ode se décline sous plusieurs format, en effet certaine amélioration permet-
    tent de ne refaire qu’un certains nombre de calcul pour optimiser le temps
    d’éxécutions. Néamoins, dans tous les cas cette contre mesure nécessite un
    temps d’éxécution supérieur car la vérification est supposé être automatique.
- Empêcher physiquement l’injection de faute ,en protégant le matériel physique
    qui exécute le DES. Cette approche est très peu utilisé car le matériel de pro-
    tection coûte souvent très cher.

## 6 Compilation et éxecutions

Le programme fournit contient un script de compilation pour compiler le pro-
gramme il suffit de tapper : make pour l’éxecution deux programmes sont disponible
:

1. ./FaultAttackAnalysis animation : propose une animation totale de toutes
    les étapes décrites dans ce document.
2. ./FaultAttackAnalysis result : donne les résultats de l’attaque.


