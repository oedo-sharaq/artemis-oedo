
{

//tree->SetAlias("tof1","sr0_x_cal[0].fTiming-dia_t_f3.fTiming");
//tree->SetAlias("tof2","dia_t_s2.fTiming-sr0_x_cal[0].fTiming");
//tree->Draw("tof1/(4*tof2):sr0_xcw[0].fPosition>>htofrx(200,-80,80,200,-0.3,-0.2)","","colz");
//tree->Draw("tof1-(4*tof2):sr0_xcw[0].fPosition>>htofrx(200,-80,80,200,-0.3,-0.2)","","colz");

tree->SetAlias("tof30","sr0_x_cal[0].fTiming-tcal_dia_strip[1].fTiming");
tree->SetAlias("tof02","tcal_dia_strip[3].fTiming-sr0_x_cal[0].fTiming");

tree->Draw("tof30-(4*tof02):sr0_xcw[0].fPosition>>htofresx(200,-80,80,200,-6850,-6730)","","colz");


}

