function x = gauss_huidai(A,b)
[~,n] = size(A);
x = zeros(n,1);
x(n)=b(n)/A(n,n);
for k=n-1:-1:1
x(k) = (b(k)-sum(A(k,k+1:n).*b(k+1:n)'))/A(k,k);
end 