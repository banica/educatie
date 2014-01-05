w=-pi:0.01:pi;
x=(1+w.^2).^(-1);
y=-w.*x;
plot(x,y);
end