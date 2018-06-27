clear
clc
close all
% 
% A = ones(3000, 1000);
% A = [12 11 2;
%     13 14 15;
%     11 22 12;
%     55 121 19;
%     14 34 56;];
% tic
% [Q1, R1] = qr(A);
% toc

X = [1;1;1];
Rp =diag([3 100 100] );
nosie1 = [0.8;10.5;16.3];
Zp = Rp*X + nosie1;
A = [12 11 2;
    13 14 15;
    11 22 12;
    16 14 21;];
nosie2 = [5.3;3.5;6.2;4.3];
L = A*X + nosie2;
AL = [A L];
allMat = [Rp Zp;AL];

[Q1, R1] = qr(AL);
xd = inv(R1(1:3,1:3))*R1(1:3,end);

% 
A=[2,-1,-1,1;
1,1,-2,1;
4,-6,2,-2;
3,6,-9,7;];
noise = [0.1;0.08;0.2;0.6];
L = [2;4;4;9] + noise;
X = [0;-1;-4;-3];
A*X - L
[Q1, R1] = qr(A);
xd = gauss_huidai(R1,L)
xd = inv(R1)*L;
A*xd - L




