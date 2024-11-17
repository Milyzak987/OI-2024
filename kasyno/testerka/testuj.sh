g++ kas.cpp -O3 -static -std=c++20 -o ./main.e

printf "UWAGA: Jeśli pamięć i czas wynosi 0 to nie są one mierzone. Zobacz komentarze w kodzie.\n"

min_odp=1000000000
max_czas=0
max_pamiec=0
avg_sum=0
echo "0" > czas.txt
echo "0" > pamiec.txt

for i in {1..100}; do
  printf "#$i:   " 
  echo $i > ./test.in

  # >> BEZ MIERZENIA CZASU I PAMIĘCI
  # ./main.e < ./test.in > ./test.out
  # if [ $? -ne 0 ]; then
  #   printf "ERROR\n"
  #   break
  # fi
  # >> KONIEC


  # >> MIERZENIE CZASU I PAMIĘCI ZA POMOCĄ OIEJQ (https://oi.edu.pl/l/srodowisko/)
  # >> UWAGA: ten skrypt NIE sprawdza czy limit pamięci został przekroczony
  oiejq/oiejq.sh ./main.e < ./test.in > test.out 2> dane.out
  dane=$(cat dane.out)
  echo "$dane" | grep "Time:" | awk '{print $2}' | sed 's/ms//' > czas.txt
  echo "$dane" | grep "Memory:" | awk '{print $2}' | sed 's/kB//' > pamiec.txt
  echo "$dane" | grep "Status:" | awk '{print $2}' > status.txt
  status=$(cat status.txt)
  if [[ "$status" != "OK" ]]; then
    printf "ERROR\n"
    break
  fi
  # >> KONIEC  

  odp=$(cat test.out)
  if (( odp < min_odp )); then 
    min_odp=$odp;
  fi

  avg_sum=$((avg_sum + odp))

  czas=$(cat czas.txt)
  if (( czas > max_czas )); then
    max_czas=$czas;
  fi

  pamiec=$(cat pamiec.txt)
  if (( pamiec > max_pamiec )); then
    max_pamiec=$pamiec
  fi
  
  printf "wyn: $odp | czas: $czas ms | pamięć: $pamiec kB   #   min_wyn: $min_odp | max_czas: $max_czas ms | max_pamięć: $max_pamiec kB\n"
done
printf "Sum average: $avg_sum \n"