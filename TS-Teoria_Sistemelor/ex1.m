t=0:0.05:4*pi;
for (w=1:9)
    y=sin(t*w);
  subplot(3,3,w);  
  plot(t,y);
end
end