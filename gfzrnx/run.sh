
# Statistics / Informations
./gfzrnx_lx -finp ABMF0020_True.18o  -stk_obs -fout ABMF0020_True.18o_stk_obs

# ASCII Timeplot of Observables
./gfzrnx_lx -finp ABMF0020_True.18o  -stk_epo 30:prn      -fout ABMF0020_True.18o_stk_epo
./gfzrnx_lx -finp ABMF0020_True.18o  -stk_epo 30:prn,otp -fout ABMF0020_True.18o_stk_epo_otp

# convert Rinex 2.0 to 3.0 ( >>>SYS / # / OBS TYPES<<< maybe bad in Rinex3.0 head)
./gfzrnx_lx -finp GRCA2070.10o -fout GRCA2070.10o_rnx3 -f

# convert Rinex 3.0 to 2.0
./gfzrnx_lx -finp ABMF0020_True.18o -fout ABMF0020_True.18o_rnx2 -vo 2

# sampling again
./gfzrnx_lx -finp ABMF0020_True.18o -fout ABMF0020_True.18o_5min -smp 300

# select satlite system and convert to Rinex2
./gfzrnx_lx -finp ABMF0020_True.18o -fout ABMF0020_True.18o_rnx2_G -satsys G -vo 2

# select satlite PRN
./gfzrnx_lx -finp ABMF0020_True.18o -fout ABMF0020_True.18o_PRN  -prn G01-10, C06-32  -no_prn G03 -f
