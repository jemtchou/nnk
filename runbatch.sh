mkdir -p jobs
cd jobs
rm -f *
begin=$2
end=$(($3-1))
geo=$1
for f in `seq $2 $end`
do
  echo "Job $f"
  cat << 'EOF' > run_$f.sh
  #PBS -N geant4_%GEO%_%RUN% 
  #PBS -l walltime=23:50:00
  #PBS -o lxpub01.jinr.ru:/scr/u/jemtchou/
  cd $TMPDIR
  cp /afs/jinr.ru/user/j/jemtchou/nnk/run.mac ./init.mac
  source /afs/jinr.ru/user/j/jemtchou/geant_setup.sh
#export G4NEUTRONHPDATA=/afs/.jinr.ru/geant4/geant4.9.6.p01/neutronhp/BROND-2.2
#export G4NEUTRONHPDATA=/afs/.jinr.ru/geant4/geant4.9.6.p01/neutronhp/CENDL-31
#export G4NEUTRONHPDATA=/afs/jinr.ru/user/j/jemtchou/geant4/neutronhp/ENDF-VI8
#export G4NEUTRONHPDATA=/afs/.jinr.ru/geant4/geant4.9.6.p01/neutronhp/ENDF-VII0
#export G4NEUTRONHPDATA=/afs/.jinr.ru/geant4/geant4.9.6.p01/neutronhp/JEFF30N
#export G4NEUTRONHPDATA=/afs/.jinr.ru/geant4/geant4.9.6.p01/neutronhp/JENDL330
#export G4NEUTRONHPDATA=/afs/.jinr.ru/geant4/geant4.9.6.p01/neutronhp/JENDL-4.0
export G4NEUTRONHPDATA=/afs/jinr.ru/user/j/jemtchou/geant4/data/G4NDL4.5/

  /afs/jinr.ru/user/j/jemtchou/nnk/build/nnk.exe init.mac %GEO% %RUN% >& run_%GEO%_%RUN%.log
  cat ./init.mac >> run_%GEO%_%RUN%.log
#  mv pos.csv pos_%RUN%.csv
  ls -l
  scp fout.root jemtchou@lxpub03.jinr.ru:/scrc/u/jemtchou/fout_%GEO%_%RUN%.root
  scp run_%GEO%_%RUN%.log jemtchou@lxpub03.jinr.ru:/scrc/u/jemtchou/
#  scp pos_%RUN%.csv jemtchou@lxpub03.jinr.ru:/scrc/u/jemtchou
EOF
  sed -i "s/%RUN%/$f/g" run_$f.sh
  sed -i "s/%GEO%/$geo/g" run_$f.sh
 
  qsub -q common run_$f.sh
done
