function [ H, v, beta ] = householder( x )
% x : inout param. x is a vector which size is n*1
% v and beta : is param which construct H matrix
% H is hoseholder Matrix. H = I - beta*v*v' 
% is sigle data
if length(x) == 1
    H = 1;
    v = 0;
    beta = 0;
    return ;
end

%derive parameter v and beta
v = zeros(size(x));
beta = zeros(size(x));

%Houserholder Algorithm begin
x_len = length(x);
x_max = max((x));
x = x./x_max;
zgama = x(2:end)'*x(2:end);
v(1) = 1;
v(2:end) = x(2:end);
if zgama == 0
    beta = 0;
else
    alpha = sqrt( x(1)^2 +  zgama);
    if x(1) <=0
        v(1) = x(1) - alpha;
    else
        v(1) = -zgama./( x(1) + alpha);
    end
    beta = 2*v(1)^2./( zgama + v(1)^2 );
    v = v./v(1);
end
%beta = 2./(v'*v);
H = eye(x_len,x_len) - beta*v*v';

end

