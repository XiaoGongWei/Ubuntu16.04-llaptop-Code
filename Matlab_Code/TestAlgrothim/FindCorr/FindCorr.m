clear
clc
close all

load CorrMat.mat

% copy to new variable
Atemp = C0625;
svd(Atemp)
cond(Atemp)

% printf svd of Atemp
svd_Atemp = svd(Atemp);
lie_Atemp = size(Atemp, 2);
store_corr  = [];
for flag_i = 1:lie_Atemp
    for flag_j = flag_i+1:lie_Atemp
        corr_ij = [flag_i, flag_j];
        corr_coff = corr( Atemp(:, flag_i), Atemp(:, flag_j));
        corr_struct.corr_ij = corr_ij;
        corr_struct.corr_coff = corr_coff;
        store_corr = [store_corr; corr_struct];
    end
end

% compute Q
M = Atemp'*Atemp;
Q = inv(M);

% stepwise
stepwise(Atemp(:,2:end), Atemp(:,1), [1,2,3,4])
