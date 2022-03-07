void calibprm(int run, double gain, int isBeam = 1) {
   double fC = 1.6e-15;
   double wf = 37.;
   double fc2MeV = 1.*fC / gain * wf;
   ofstream fout(Form("fc2MeV.%d.prm",run));
   for (int i = 0; i < 4048; ++i) {
      if (isBeam && (i%23) < 2 ||
          !isBeam && (i%23) > 2) {
         fout << 0. << fc2MeV;
      } else {
         fout << 0. << 1.;
      }
   }
}
