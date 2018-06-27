clear
clc
close all

% example 1: use vector x as test
x = [1;1;1];
x = ones(100000,1) * 5.5;
x = [[-2.64206170089262;0.707938299107378]];
%x = [0;0;2.35;0];
tic
[H, v, beta] = householder(x);
toc
x_hoserholder = H*x;
w = beta*x'*v
x_hoserholder1 = x - v*w'
disp(x_hoserholder)

% example 2: use matrix A as test
A = [1 1 1;1 1 1;1 1 1];
tic
[Q1, R1] = qr(A);
toc
tic
A_hang = size(A,1);
A_lie = size(A,2);
H = cell( A_lie, 1 );
Hs = eye(A_hang, A_hang);
R2 = A;
Q2 = eye(A_hang,A_hang);
i = i + 1
for i = 1:A_lie
    [Hi, vi, betai] = householder(R2(i:end,i));
    %H{i} = blkdiag(eye(i-1), Hi);
    R2(i:end,i:end) = Hi*R2(i:end,i:end);
    Q2 = Q2*blkdiag(eye(i-1), Hi);
end
Q2(find(abs(Q2) < 1e-10)) = 0;
R2(find(abs(R2) < 1e-10)) = 0;
toc
Q1*R1 - A
Q2*R2 - A
erroQ = Q1 + Q2
erroR = R1 + R2




%��Խǻ���?
n=length(A);
Q=eye(n);
for k=1:n-2
    [v,b]=householder(A(k+1:n,k));
    b = b';
    u=b*A(k+1:n,k+1:n)*v;
    w=u-(b*u'*v/2)*v;
    Hk=eye(n-k)-b*(v*v');
    H=blkdiag(eye(k),Hk);
    Q=Q*H;
    A(k+1,k)=norm(A(k+1:n,k));
    A(k,k+1)=A(k+1,k);
    A(k,k+2:n)=0;
    A(k+2:n,k)=0;
    A(k+1:n,k+1:n)=A(k+1:n,k+1:n)-v*w'-w*v';
end
T=A
Q
disp(Q*T*Q');




%use hoserholder translate x vector




