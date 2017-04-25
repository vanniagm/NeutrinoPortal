(* ::Package:: *)

SetDirectory["/home/vanniagm/Dropbox/nu_portal/MATH_NUMODEL"]


ps = {{148,83}, {443,84}, {739,84},{828,84}, {1035,82}}


xs = {{10.,10.^(-16)}, {10.^2,10.^(-16)}, {10.^3,10.^(-16)}, {2. 10^3,10.^(-16)}, {10.^4,10.^(-16)}}


qs = {{148,83},{148,261}, {149,439}, {147,616}, {148,794},{147,971}}


ys = {{10., 10.^(-16)}, {10., 10.^(-15)},{10., 10.^(-14)}, {10., 10.^(-13)},{10., 10.^(-12)},{10., 10.^(-11)}}


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


FSK = Interpolation[{{225,452},{271,447},{326,439},{382,430},{430,424},{470,416},{518,406},{558,401},{609,396},{659,390},{729,382},{781,379},{857,381},{944,381},{1035,379}}, InterpolationOrder -> 1]


(* ::Input:: *)
(**)


Subscript[\[CapitalPhi], \[Mu]][m\[CapitalPsi]_] := E^((FSK[ap + mp*Log[m\[CapitalPsi]]] - aq)/mq)


pic = LogLogPlot[Subscript[\[CapitalPhi], \[Mu]][m], {m, 18, 10.^4},PlotRange->{10.^-16,10^-11}]


Export["UpMuonFluxSK.png", pic]
