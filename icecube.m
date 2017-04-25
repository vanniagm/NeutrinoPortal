(* ::Package:: *)

(* ::Input:: *)
(*SetDirectory["/home/vanniagm/Dropbox/nu_portal/MATH_NUMODEL"]*)


ps = {{473.3,192.443}, {553.78,192.443}, {601.,192.443},{740.5,192.443}, {821.,192.443}}


xs = {{100.,10.^(-25)}, {200.,10.^(-25)}, {300.,10.^(-25)}, {1000.,10.^(-25)}, {1200.,10.^(-25)}}


qs = {{473.3,192.443},{473.3,290.12}, {473.3,385.623}, {473.3,483.3}, {473.3,580.95}}


ys = {{100., 10.^(-25)}, {100., 10.^(-24)},{100., 10.^(-23)}, {100., 10.^(-22)},{100., 10.^(-21)}}


(* ::Input:: *)
(**)


pp = Fit[Table[{xs[[i,1]], ps[[i,1]]}, {i, 1, 5}], {1, Log[u]}, u]
ap = pp /. u -> 1
mp = pp - ap /. u -> E


(* ::Input:: *)
(**)


qq = Fit[Table[{ys[[i,2]], qs[[i,2]]}, {i, 1, 4}], {1, Log[u]}, u]
aq = qq /. u -> 1
mq = qq - aq /. u -> E


(* ::Input:: *)
(**)


FSK = Interpolation[{{474.4,510.2},{508.7,481.1},{553.8,443.6},{578.5,435},{601.,425.3},{620.3,422.1},{635.3,417.8},{661.1,415.7},{698.67,412.45},{714.8,414.6},{727.6,412.4},{777.,416.7},{821.,418.9}}, InterpolationOrder -> 1]


(* ::Input:: *)
(**)


Subscript[\[CapitalPhi], \[Mu]][m\[CapitalPsi]_] := E^((FSK[ap + mp*Log[m\[CapitalPsi]]] - aq)/mq)


data3 = Cases[Plot[Subscript[\[CapitalPhi], \[Mu]][m], {m, 100, 200}], Line[data_] :> data, -4, 
    1][[1]];

Export["icecube.dat", data3]


pic = LogPlot[Subscript[\[CapitalPhi], \[Mu]][m], {m, 100, 200},PlotRange->{10.^-25,10.^-21}]






