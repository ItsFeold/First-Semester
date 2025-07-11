## ΠΕΡΙΓΡΑΦΗ

<p align="center">

Το πρόγραμμα gcd.c αποτελεί υλοποίηση μιας μοντέρνας εκδοχής του ["Ευκλείδιου Αλγορίθμου"](https://en.wikipedia.org/wiki/Euclidean_algorithm), ενός αλγορίθμου ο οποίος υπολογίζει αποδοτικά το Μέγιστο Κοινό Διαιρέτη(ΜΚΔ) δύο ακεραίων αριθμών. Το πρόγραμμα αυτό δέχεται από την γραμμή εντολών δύο ακέραιους αριθμούς, και χρησιμοποιώντας τον αλγόριθμο του Ευκλείδη τυπώνει τον μέγιστο κοινό διαιρέτη(ΜΚΔ) των δύο αριθμών αυτών. Εαν η είσοδος είναι έγκυρη (δωθούν τιμές εντός προδιαγραφών) τότε εφόσον τυπώσει το ΜΚΔ, τερματίζει με κωδικό εξόδου `0`. Εαν η είσοδος δεν είναι έγκυρη, τότε το πρόγραμμα τυπώνει οδηγίες για την ορθή χρήση του και τερματίζει με κωδικό εξόδου `1`. 

</p>

## COMPILATION 
Για την μεταγλώτισση του προγράμματος αρκεί η εκτέλεση της παρακάτω εντολής στην γραμμή εντολών.

```sh
 gcc -O0 -m32 -Wall -Wextra -Werror -pedantic -o gcd gcd.c
```

</p>

## ΠΡΟΑΠΑΙΤΟΥΜΕΝΑ
- Χρειάζεται το `libgcc-multilib`
- Χρειάζεται ο μεταγλωττιστής `gcc`
  Η εγκατάσταση τους μπορεί να γίνει με την ακόλουθη εντολή:

```sh
apt-get install gcc gcc-multilib
```
  
</p>

## ΤΕΧΝΙΚΕΣ ΠΡΟΔΙΑΓΡΑΦΕΣ
To πρόγραμμα:
- Ολοκληρώνει την εκτέλεση του μέσα σε 1 δετερόλεπτο
- Είναι γραμμένο σε γλώσσα C.
- Χρησιμοποιεί αναδρομική συνάρτηση
- Επεξεργάζεται ακέραιες τιμές με εύρος {-10^18, 10^18}
  
  
Στον ίδιο φάκελο (gcd) περιέχονται και δύο txt αρχεία (input.txt και output.txt) που περιέχουν στοιχεία εισόδου και εξόδου αντίστοιχα.


## DEMO 
Παραδείγματα εκτέλεσης του προγράμματος σε Linux: 

```sh
$ gcc -O3 -Wall -Wextra -Werror -pedantic -o gcd gcd.c
$ ./gcd
Usage: ./gcd <num1> <num2>
$ echo $?
1
$ ./gcd 1
Usage: ./gcd <num1> <num2>
$ echo $?
1
$ ./gcd 18 42
gcd(18, 42) = 6
$ ./gcd -52 40
gcd(-52, 40) = 4
$ ./gcd 102 44
gcd(102, 44) = 2
$ echo $?
0
$ ./gcd 432 45 5345
Usage: ./gcd <num1> <num2>
$ echo $?
1
$ ./gcd 9453000000000 2323400000000
gcd(9453000000000, 2323400000000) = 200000000
$ echo $?
0
$ ./gcd 5464565423 123675675781
gcd(5464565423, 123675675781) = 1
$ echo $?
0
$ time ./gcd 1000000000000000000 999999999999999999
gcd(1000000000000000000, 999999999999999999) = 1

real    0m0.001s
user    0m0.000s
sys     0m0.000s
```
