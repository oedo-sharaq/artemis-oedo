/*
 * @file   TSRPPACPlaneStripDqdxProcessor.cc
 * @brief  sr-ppac plane processor with dqdx
 */

#include "TSRPPACPlaneStripDqdxProcessor.h"
#include "TMonotoneTableConverter.h"
#include "TMath.h"
//#include <iostream>
#include <fstream>

using art::TSRPPACPlaneStripDqdxProcessor;

ClassImp(TSRPPACPlaneStripDqdxProcessor)

TSRPPACPlaneStripDqdxProcessor::TSRPPACPlaneStripDqdxProcessor()
{
   RegisterInputInfo("Converter","name of dqdx converter",fConverterName,"srppac_xc0",
                     &fConverter, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter01","name of dqdx converter",fConverterName01,"srppac_xc0",
                     &fConverter01, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter10","name of dqdx converter",fConverterName10,"srppac_xc0",
                     &fConverter10, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter12","name of dqdx converter",fConverterName12,"srppac_xc0",
                     &fConverter12, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter21","name of dqdx converter",fConverterName21,"srppac_xc0",
                     &fConverter21, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter23","name of dqdx converter",fConverterName23,"srppac_xc0",
                     &fConverter23, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter32","name of dqdx converter",fConverterName32,"srppac_xc0",
                     &fConverter32, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter34","name of dqdx converter",fConverterName34,"srppac_xc0",
                     &fConverter34, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter43","name of dqdx converter",fConverterName43,"srppac_xc0",
                     &fConverter43, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter45","name of dqdx converter",fConverterName45,"srppac_xc0",
                     &fConverter45, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter54","name of dqdx converter",fConverterName54,"srppac_xc0",
                     &fConverter54, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter56","name of dqdx converter",fConverterName56,"srppac_xc0",
                     &fConverter56, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter65","name of dqdx converter",fConverterName65,"srppac_xc0",
                     &fConverter65, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter67","name of dqdx converter",fConverterName67,"srppac_xc0",
                     &fConverter67, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter76","name of dqdx converter",fConverterName76,"srppac_xc0",
                     &fConverter76, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter78","name of dqdx converter",fConverterName78,"srppac_xc0",
                     &fConverter78, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter87","name of dqdx converter",fConverterName87,"srppac_xc0",
                     &fConverter87, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter89","name of dqdx converter",fConverterName89,"srppac_xc0",
                     &fConverter89, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter98","name of dqdx converter",fConverterName98,"srppac_xc0",
                     &fConverter98, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter910","name of dqdx converter",fConverterName910,"srppac_xc0",
                     &fConverter910, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter109","name of dqdx converter",fConverterName109,"srppac_xc0",
                     &fConverter109, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1011","name of dqdx converter",fConverterName1011,"srppac_xc0",
                     &fConverter1011, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1110","name of dqdx converter",fConverterName1110,"srppac_xc0",
                     &fConverter1110, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1112","name of dqdx converter",fConverterName1112,"srppac_xc0",
                     &fConverter1112, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1211","name of dqdx converter",fConverterName1211,"srppac_xc0",
                     &fConverter1211, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1213","name of dqdx converter",fConverterName1213,"srppac_xc0",
                     &fConverter1213, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1312","name of dqdx converter",fConverterName1312,"srppac_xc0",
                     &fConverter1312, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1314","name of dqdx converter",fConverterName1314,"srppac_xc0",
                     &fConverter1314, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1413","name of dqdx converter",fConverterName1413,"srppac_xc0",
                     &fConverter1413, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1415","name of dqdx converter",fConverterName1415,"srppac_xc0",
                     &fConverter1415, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1514","name of dqdx converter",fConverterName1514,"srppac_xc0",
                     &fConverter1514, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1516","name of dqdx converter",fConverterName1516,"srppac_xc0",
                     &fConverter1516, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1615","name of dqdx converter",fConverterName1615,"srppac_xc0",
                     &fConverter1615, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1617","name of dqdx converter",fConverterName1617,"srppac_xc0",
                     &fConverter1617, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1716","name of dqdx converter",fConverterName1716,"srppac_xc0",
                     &fConverter1716, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1718","name of dqdx converter",fConverterName1718,"srppac_xc0",
                     &fConverter1718, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1817","name of dqdx converter",fConverterName1817,"srppac_xc0",
                     &fConverter1817, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1819","name of dqdx converter",fConverterName1819,"srppac_xc0",
                     &fConverter1819, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1918","name of dqdx converter",fConverterName1918,"srppac_xc0",
                     &fConverter1918, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1920","name of dqdx converter",fConverterName1920,"srppac_xc0",
                     &fConverter1920, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2019","name of dqdx converter",fConverterName2019,"srppac_xc0",
                     &fConverter2019, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2021","name of dqdx converter",fConverterName2021,"srppac_xc0",
                     &fConverter2021, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2120","name of dqdx converter",fConverterName2120,"srppac_xc0",
                     &fConverter2120, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2122","name of dqdx converter",fConverterName2122,"srppac_xc0",
                     &fConverter2122, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2221","name of dqdx converter",fConverterName2221,"srppac_xc0",
                     &fConverter2221, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2223","name of dqdx converter",fConverterName2223,"srppac_xc0",
                     &fConverter2223, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2322","name of dqdx converter",fConverterName2322,"srppac_xc0",
                     &fConverter2322, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2324","name of dqdx converter",fConverterName2324,"srppac_xc0",
                     &fConverter2324, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2423","name of dqdx converter",fConverterName2423,"srppac_xc0",
                     &fConverter2423, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2425","name of dqdx converter",fConverterName2425,"srppac_xc0",
                     &fConverter2425, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2524","name of dqdx converter",fConverterName2524,"srppac_xc0",
                     &fConverter2524, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2526","name of dqdx converter",fConverterName2526,"srppac_xc0",
                     &fConverter2526, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2625","name of dqdx converter",fConverterName2625,"srppac_xc0",
                     &fConverter2625, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2627","name of dqdx converter",fConverterName2627,"srppac_xc0",
                     &fConverter2627, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2726","name of dqdx converter",fConverterName2726,"srppac_xc0",
                     &fConverter2726, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2728","name of dqdx converter",fConverterName2728,"srppac_xc0",
                     &fConverter2728, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2827","name of dqdx converter",fConverterName2827,"srppac_xc0",
                     &fConverter2827, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2829","name of dqdx converter",fConverterName2829,"srppac_xc0",
                     &fConverter2829, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2928","name of dqdx converter",fConverterName2928,"srppac_xc0",
                     &fConverter2928, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2930","name of dqdx converter",fConverterName2930,"srppac_xc0",
                     &fConverter2930, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3029","name of dqdx converter",fConverterName3029,"srppac_xc0",
                     &fConverter3029, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3031","name of dqdx converter",fConverterName3031,"srppac_xc0",
                     &fConverter3031, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3130","name of dqdx converter",fConverterName3130,"srppac_xc0",
                     &fConverter3130, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3132","name of dqdx converter",fConverterName3132,"srppac_xc0",
                     &fConverter3132, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3231","name of dqdx converter",fConverterName3231,"srppac_xc0",
                     &fConverter3231, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3233","name of dqdx converter",fConverterName3233,"srppac_xc0",
                     &fConverter3233, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3332","name of dqdx converter",fConverterName3332,"srppac_xc0",
                     &fConverter3332, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3334","name of dqdx converter",fConverterName3334,"srppac_xc0",
                     &fConverter3334, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3433","name of dqdx converter",fConverterName3433,"srppac_xc0",
                     &fConverter3433, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3435","name of dqdx converter",fConverterName3435,"srppac_xc0",
                     &fConverter3435, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3534","name of dqdx converter",fConverterName3534,"srppac_xc0",
                     &fConverter3534, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3536","name of dqdx converter",fConverterName3536,"srppac_xc0",
                     &fConverter3536, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3635","name of dqdx converter",fConverterName3635,"srppac_xc0",
                     &fConverter3635, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3637","name of dqdx converter",fConverterName3637,"srppac_xc0",
                     &fConverter3637, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3736","name of dqdx converter",fConverterName3736,"srppac_xc0",
                     &fConverter3736, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3738","name of dqdx converter",fConverterName3738,"srppac_xc0",
                     &fConverter3738, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3837","name of dqdx converter",fConverterName3837,"srppac_xc0",
                     &fConverter3837, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3839","name of dqdx converter",fConverterName3839,"srppac_xc0",
                     &fConverter3839, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3938","name of dqdx converter",fConverterName3938,"srppac_xc0",
                     &fConverter3938, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter3940","name of dqdx converter",fConverterName3940,"srppac_xc0",
                     &fConverter3940, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4039","name of dqdx converter",fConverterName4039,"srppac_xc0",
                     &fConverter4039, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4041","name of dqdx converter",fConverterName4041,"srppac_xc0",
                     &fConverter4041, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4140","name of dqdx converter",fConverterName4140,"srppac_xc0",
                     &fConverter4140, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4142","name of dqdx converter",fConverterName4142,"srppac_xc0",
                     &fConverter4142, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4241","name of dqdx converter",fConverterName4241,"srppac_xc0",
                     &fConverter4241, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4243","name of dqdx converter",fConverterName4243,"srppac_xc0",
                     &fConverter4243, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4342","name of dqdx converter",fConverterName4342,"srppac_xc0",
                     &fConverter4342, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4344","name of dqdx converter",fConverterName4344,"srppac_xc0",
                     &fConverter4344, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4443","name of dqdx converter",fConverterName4443,"srppac_xc0",
                     &fConverter4443, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4445","name of dqdx converter",fConverterName4445,"srppac_xc0",
                     &fConverter4445, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4544","name of dqdx converter",fConverterName4544,"srppac_xc0",
                     &fConverter4544, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4546","name of dqdx converter",fConverterName4546,"srppac_xc0",
                     &fConverter4546, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4645","name of dqdx converter",fConverterName4645,"srppac_xc0",
                     &fConverter4645, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4647","name of dqdx converter",fConverterName4647,"srppac_xc0",
                     &fConverter4647, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4746","name of dqdx converter",fConverterName4746,"srppac_xc0",
                     &fConverter4746, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4748","name of dqdx converter",fConverterName4748,"srppac_xc0",
                     &fConverter4748, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4847","name of dqdx converter",fConverterName4847,"srppac_xc0",
                     &fConverter4847, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4849","name of dqdx converter",fConverterName4849,"srppac_xc0",
                     &fConverter4849, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4948","name of dqdx converter",fConverterName4948,"srppac_xc0",
                     &fConverter4948, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter4950","name of dqdx converter",fConverterName4950,"srppac_xc0",
                     &fConverter4950, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5049","name of dqdx converter",fConverterName5049,"srppac_xc0",
                     &fConverter5049, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5051","name of dqdx converter",fConverterName5051,"srppac_xc0",
                     &fConverter5051, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5150","name of dqdx converter",fConverterName5150,"srppac_xc0",
                     &fConverter5150, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5152","name of dqdx converter",fConverterName5152,"srppac_xc0",
                     &fConverter5152, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5251","name of dqdx converter",fConverterName5251,"srppac_xc0",
                     &fConverter5251, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5253","name of dqdx converter",fConverterName5253,"srppac_xc0",
                     &fConverter5253, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5352","name of dqdx converter",fConverterName5352,"srppac_xc0",
                     &fConverter5352, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5354","name of dqdx converter",fConverterName5354,"srppac_xc0",
                     &fConverter5354, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5453","name of dqdx converter",fConverterName5453,"srppac_xc0",
                     &fConverter5453, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5455","name of dqdx converter",fConverterName5455,"srppac_xc0",
                     &fConverter5455, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5554","name of dqdx converter",fConverterName5554,"srppac_xc0",
                     &fConverter5554, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5556","name of dqdx converter",fConverterName5556,"srppac_xc0",
                     &fConverter5556, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5655","name of dqdx converter",fConverterName5655,"srppac_xc0",
                     &fConverter5655, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5657","name of dqdx converter",fConverterName5657,"srppac_xc0",
                     &fConverter5657, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5756","name of dqdx converter",fConverterName5756,"srppac_xc0",
                     &fConverter5756, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5758","name of dqdx converter",fConverterName5758,"srppac_xc0",
                     &fConverter5758, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5857","name of dqdx converter",fConverterName5857,"srppac_xc0",
                     &fConverter5857, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5859","name of dqdx converter",fConverterName5859,"srppac_xc0",
                     &fConverter5859, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5958","name of dqdx converter",fConverterName5958,"srppac_xc0",
                     &fConverter5958, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter5960","name of dqdx converter",fConverterName5960,"srppac_xc0",
                     &fConverter5960, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6059","name of dqdx converter",fConverterName6059,"srppac_xc0",
                     &fConverter6059, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6061","name of dqdx converter",fConverterName6061,"srppac_xc0",
                     &fConverter6061, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6160","name of dqdx converter",fConverterName6160,"srppac_xc0",
                     &fConverter6160, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6162","name of dqdx converter",fConverterName6162,"srppac_xc0",
                     &fConverter6162, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6261","name of dqdx converter",fConverterName6261,"srppac_xc0",
                     &fConverter6261, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6263","name of dqdx converter",fConverterName6263,"srppac_xc0",
                     &fConverter6263, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6362","name of dqdx converter",fConverterName6362,"srppac_xc0",
                     &fConverter6362, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6364","name of dqdx converter",fConverterName6364,"srppac_xc0",
                     &fConverter6364, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6463","name of dqdx converter",fConverterName6463,"srppac_xc0",
                     &fConverter6463, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6465","name of dqdx converter",fConverterName6465,"srppac_xc0",
                     &fConverter6465, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6564","name of dqdx converter",fConverterName6564,"srppac_xc0",
                     &fConverter6564, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6566","name of dqdx converter",fConverterName6566,"srppac_xc0",
                     &fConverter6566, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6665","name of dqdx converter",fConverterName6665,"srppac_xc0",
                     &fConverter6665, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6667","name of dqdx converter",fConverterName6667,"srppac_xc0",
                     &fConverter6667, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6766","name of dqdx converter",fConverterName6766,"srppac_xc0",
                     &fConverter6766, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6768","name of dqdx converter",fConverterName6768,"srppac_xc0",
                     &fConverter6768, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6867","name of dqdx converter",fConverterName6867,"srppac_xc0",
                     &fConverter6867, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6869","name of dqdx converter",fConverterName6869,"srppac_xc0",
                     &fConverter6869, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6968","name of dqdx converter",fConverterName6968,"srppac_xc0",
                     &fConverter6968, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter6970","name of dqdx converter",fConverterName6970,"srppac_xc0",
                     &fConverter6970, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7069","name of dqdx converter",fConverterName7069,"srppac_xc0",
                     &fConverter7069, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7071","name of dqdx converter",fConverterName7071,"srppac_xc0",
                     &fConverter7071, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7170","name of dqdx converter",fConverterName7170,"srppac_xc0",
                     &fConverter7170, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7172","name of dqdx converter",fConverterName7172,"srppac_xc0",
                     &fConverter7172, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7271","name of dqdx converter",fConverterName7271,"srppac_xc0",
                     &fConverter7271, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7273","name of dqdx converter",fConverterName7273,"srppac_xc0",
                     &fConverter7273, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7372","name of dqdx converter",fConverterName7372,"srppac_xc0",
                     &fConverter7372, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7374","name of dqdx converter",fConverterName7374,"srppac_xc0",
                     &fConverter7374, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7473","name of dqdx converter",fConverterName7473,"srppac_xc0",
                     &fConverter7473, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7475","name of dqdx converter",fConverterName7475,"srppac_xc0",
                     &fConverter7475, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7574","name of dqdx converter",fConverterName7574,"srppac_xc0",
                     &fConverter7574, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7576","name of dqdx converter",fConverterName7576,"srppac_xc0",
                     &fConverter7576, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7675","name of dqdx converter",fConverterName7675,"srppac_xc0",
                     &fConverter7675, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7677","name of dqdx converter",fConverterName7677,"srppac_xc0",
                     &fConverter7677, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7776","name of dqdx converter",fConverterName7776,"srppac_xc0",
                     &fConverter7776, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7778","name of dqdx converter",fConverterName7778,"srppac_xc0",
                     &fConverter7778, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7877","name of dqdx converter",fConverterName7877,"srppac_xc0",
                     &fConverter7877, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7879","name of dqdx converter",fConverterName7879,"srppac_xc0",
                     &fConverter7879, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7978","name of dqdx converter",fConverterName7978,"srppac_xc0",
                     &fConverter7978, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter7980","name of dqdx converter",fConverterName7980,"srppac_xc0",
                     &fConverter7980, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8079","name of dqdx converter",fConverterName8079,"srppac_xc0",
                     &fConverter8079, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8081","name of dqdx converter",fConverterName8081,"srppac_xc0",
                     &fConverter8081, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8180","name of dqdx converter",fConverterName8180,"srppac_xc0",
                     &fConverter8180, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8182","name of dqdx converter",fConverterName8182,"srppac_xc0",
                     &fConverter8182, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8281","name of dqdx converter",fConverterName8281,"srppac_xc0",
                     &fConverter8281, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8283","name of dqdx converter",fConverterName8283,"srppac_xc0",
                     &fConverter8283, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8382","name of dqdx converter",fConverterName8382,"srppac_xc0",
                     &fConverter8382, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8384","name of dqdx converter",fConverterName8384,"srppac_xc0",
                     &fConverter8384, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8483","name of dqdx converter",fConverterName8483,"srppac_xc0",
                     &fConverter8483, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8485","name of dqdx converter",fConverterName8485,"srppac_xc0",
                     &fConverter8485, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8584","name of dqdx converter",fConverterName8584,"srppac_xc0",
                     &fConverter8584, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8586","name of dqdx converter",fConverterName8586,"srppac_xc0",
                     &fConverter8586, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8685","name of dqdx converter",fConverterName8685,"srppac_xc0",
                     &fConverter8685, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8687","name of dqdx converter",fConverterName8687,"srppac_xc0",
                     &fConverter8687, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8786","name of dqdx converter",fConverterName8786,"srppac_xc0",
                     &fConverter8786, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8788","name of dqdx converter",fConverterName8788,"srppac_xc0",
                     &fConverter8788, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8887","name of dqdx converter",fConverterName8887,"srppac_xc0",
                     &fConverter8887, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8889","name of dqdx converter",fConverterName8889,"srppac_xc0",
                     &fConverter8889, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8988","name of dqdx converter",fConverterName8988,"srppac_xc0",
                     &fConverter8988, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter8990","name of dqdx converter",fConverterName8990,"srppac_xc0",
                     &fConverter8990, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter9089","name of dqdx converter",fConverterName9089,"srppac_xc0",
                     &fConverter9089, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter9091","name of dqdx converter",fConverterName9091,"srppac_xc0",
                     &fConverter9091, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter9190","name of dqdx converter",fConverterName9190,"srppac_xc0",
                     &fConverter9190, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter9192","name of dqdx converter",fConverterName9192,"srppac_xc0",
                     &fConverter9192, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter9291","name of dqdx converter",fConverterName9291,"srppac_xc0",
                     &fConverter9291, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter9293","name of dqdx converter",fConverterName9293,"srppac_xc0",
                     &fConverter9293, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter9392","name of dqdx converter",fConverterName9392,"srppac_xc0",
                     &fConverter9392, "art::TMonotoneTableConverter");
   RegisterProcessorParameter("Combination","type of combination: 0 => ID0-ID1, 1 => ID1-ID2",fCombination,0);
}




TSRPPACPlaneStripDqdxProcessor::~TSRPPACPlaneStripDqdxProcessor()
{
}

void TSRPPACPlaneStripDqdxProcessor::Process()
{
   fOutput->Clear("C");
   if((*fInput)->GetEntriesFast() < 2 ) return;

   double pos = 0.;
   double c0 = 0.;
   double c1 = 0.;
   double c2 = 0.;
   int id0 = 0;
   int id1 = 0;
   int id2 = 0;
   TTimingChargeData* inData0;   
   TTimingChargeData* inData1;   
   TTimingChargeData* inData2;   

//   printf("%p\n",*fConverter);
   if (fCombination == 0 && (*fInput)->GetEntriesFast() > 1) {
      inData0 = static_cast<TTimingChargeData*>((*fInput)->UncheckedAt(0));
      inData1 = static_cast<TTimingChargeData*>((*fInput)->UncheckedAt(1));
      id0 = inData0->GetID();
      id1 = inData1->GetID();
      c0 = inData0->GetCharge();
      c1 = inData1->GetCharge();
      if (TMath::IsNaN(c0) || TMath::IsNaN(c1)) return;

      /*
      std::cout << "ID0=" << id0 << std::endl << "ID1=" << id1 << std::endl;
      std::cout << "C0=" << c0 << std::endl << "C1=" << c1 << std::endl;
      std::cout << "C00=" << c00 << std::endl << "C11=" << c11 << std::endl;
      std::cout << "gain0=" << gain[id0] << std::endl << "gain1=" << gain[id1] << std::endl;
      */

      if(id0 == 0 && id1 == 1){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter01)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 1 && id1 == 0){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter10)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 1 && id1 == 2){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter12)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 2 && id1 == 1){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter21)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 2 && id1 == 3){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter23)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 3 && id1 == 2){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter32)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 3 && id1 == 4){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter34)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 4 && id1 == 3){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter43)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 4 && id1 == 5){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter45)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 5 && id1 == 4){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter54)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 5 && id1 == 6){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter56)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 6 && id1 == 5){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter65)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 6 && id1 == 7){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter67)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 7 && id1 == 6){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter76)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 7 && id1 == 8){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter78)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 8 && id1 == 7){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter87)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 8 && id1 == 9){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter89)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 9 && id1 == 8){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter98)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 9 && id1 == 10){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter910)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 10 && id1 == 9){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter109)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 10 && id1 == 11){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter1011)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 11 && id1 == 10){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter1110)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 11 && id1 == 12){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter1112)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 12 && id1 == 11){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter1211)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 12 && id1 == 13){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter1213)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 13 && id1 == 12){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter1312)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 13 && id1 == 14){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter1314)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 14 && id1 == 13){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter1413)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 14 && id1 == 15){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter1415)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 15 && id1 == 14){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter1514)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 15 && id1 == 16){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter1516)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 16 && id1 == 15){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter1615)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 16 && id1 == 17){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter1617)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 17 && id1 == 16){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter1716)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 17 && id1 == 18){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter1718)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 18 && id1 == 17){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter1817)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 18 && id1 == 19){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter1819)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 19 && id1 == 18){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter1918)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 19 && id1 == 20){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter1920)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 20 && id1 == 19){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2019)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 20 && id1 == 21){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2021)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 21 && id1 == 20){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2120)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 21 && id1 == 22){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2122)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 22 && id1 == 21){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2221)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 22 && id1 == 23){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2223)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 23 && id1 == 22){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2322)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 23 && id1 == 24){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2324)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 24 && id1 == 23){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2423)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 24 && id1 == 25){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2425)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 25 && id1 == 24){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2524)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 25 && id1 == 26){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2526)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 26 && id1 == 25){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2625)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 26 && id1 == 27){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2627)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 27 && id1 == 26){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2726)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 27 && id1 == 28){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2728)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 28 && id1 == 27){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2827)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 28 && id1 == 29){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2829)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 29 && id1 == 28){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2928)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 29 && id1 == 30){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter2930)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 30 && id1 == 29){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3029)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 30 && id1 == 31){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3031)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 31 && id1 == 30){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3130)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 31 && id1 == 32){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3132)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 32 && id1 == 31){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3231)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 32 && id1 == 33){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3233)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 33 && id1 == 32){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3332)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 33 && id1 == 34){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3334)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 34 && id1 == 33){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3433)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 34 && id1 == 35){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3435)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 35 && id1 == 34){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3534)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 35 && id1 == 36){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3536)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 36 && id1 == 35){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3635)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 36 && id1 == 37){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3637)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 37 && id1 == 36){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3736)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 37 && id1 == 38){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3738)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 38 && id1 == 37){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3837)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 38 && id1 == 39){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3839)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 39 && id1 == 38){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3938)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 39 && id1 == 40){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter3940)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 40 && id1 == 39){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4039)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 40 && id1 == 41){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4041)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 41 && id1 == 40){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4140)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 41 && id1 == 42){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4142)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 42 && id1 == 41){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4241)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 42 && id1 == 43){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4243)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 43 && id1 == 42){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4342)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 43 && id1 == 44){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4344)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 44 && id1 == 43){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4443)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 44 && id1 == 45){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4445)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 45 && id1 == 44){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4544)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 45 && id1 == 46){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4546)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 46 && id1 == 45){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4645)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 46 && id1 == 47){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4647)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 47 && id1 == 46){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4746)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 47 && id1 == 48){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4748)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 48 && id1 == 47){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4847)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 48 && id1 == 49){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4849)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 49 && id1 == 48){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4948)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 49 && id1 == 50){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter4950)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 50 && id1 == 49){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5049)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 50 && id1 == 51){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5051)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 51 && id1 == 50){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5150)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 51 && id1 == 52){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5152)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 52 && id1 == 51){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5251)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 52 && id1 == 53){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5253)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 53 && id1 == 52){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5352)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 53 && id1 == 54){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5354)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 54 && id1 == 53){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5453)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 54 && id1 == 55){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5455)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 55 && id1 == 54){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5554)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 55 && id1 == 56){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5556)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 56 && id1 == 55){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5655)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 56 && id1 == 57){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5657)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 57 && id1 == 56){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5756)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 57 && id1 == 58){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5758)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 58 && id1 == 57){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5857)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 58 && id1 == 59){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5859)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 59 && id1 == 58){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5958)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 59 && id1 == 60){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter5960)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 60 && id1 == 59){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6059)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 60 && id1 == 61){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6061)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 61 && id1 == 60){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6160)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 61 && id1 == 62){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6162)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 62 && id1 == 61){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6261)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 62 && id1 == 63){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6263)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 63 && id1 == 62){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6362)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 63 && id1 == 64){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6364)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 64 && id1 == 63){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6463)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 64 && id1 == 65){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6465)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 65 && id1 == 64){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6564)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 65 && id1 == 66){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6566)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 66 && id1 == 65){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6665)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 66 && id1 == 67){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6667)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 67 && id1 == 66){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6766)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 67 && id1 == 68){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6768)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 68 && id1 == 67){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6867)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 68 && id1 == 69){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6869)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 69 && id1 == 68){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6968)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 69 && id1 == 70){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter6970)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 70 && id1 == 69){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7069)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 70 && id1 == 71){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7071)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 71 && id1 == 70){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7170)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 71 && id1 == 72){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7172)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 72 && id1 == 71){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7271)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 72 && id1 == 73){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7273)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 73 && id1 == 72){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7372)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 73 && id1 == 74){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7374)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 74 && id1 == 73){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7473)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 74 && id1 == 75){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7475)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 75 && id1 == 74){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7574)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 75 && id1 == 76){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7576)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 76 && id1 == 75){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7675)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 76 && id1 == 77){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7677)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 77 && id1 == 76){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7776)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 77 && id1 == 78){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7778)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 78 && id1 == 77){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7877)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 78 && id1 == 79){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7879)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 79 && id1 == 78){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7978)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 79 && id1 == 80){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter7980)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 80 && id1 == 79){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8079)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 80 && id1 == 81){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8081)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 81 && id1 == 80){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8180)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 81 && id1 == 82){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8182)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 82 && id1 == 81){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8281)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 82 && id1 == 83){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8283)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 83 && id1 == 82){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8382)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 83 && id1 == 84){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8384)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 84 && id1 == 83){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8483)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 84 && id1 == 85){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8485)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 85 && id1 == 84){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8584)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 85 && id1 == 86){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8586)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 86 && id1 == 85){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8685)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 86 && id1 == 87){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8687)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 87 && id1 == 86){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8786)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 87 && id1 == 88){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8788)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 88 && id1 == 87){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8887)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 88 && id1 == 89){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8889)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 89 && id1 == 88){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8988)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 89 && id1 == 90){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter8990)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 91 && id1 == 90){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter9190)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 91 && id1 == 92){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter9192)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 92 && id1 == 91){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter9291)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 92 && id1 == 93){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter9293)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else if(id0 == 93 && id1 == 92){
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter9392)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }else{
         pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (1 - (*fConverter)->Convert((c0 - c1)/(c0 + c1))) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
      }
      //std::cout << "pos=" << pos << std::endl;
      
   } else if (fCombination == 1 && (*fInput)->GetEntriesFast() > 2) {
      inData0 = static_cast<TTimingChargeData*>((*fInput)->UncheckedAt(0));
      inData1 = static_cast<TTimingChargeData*>((*fInput)->UncheckedAt(1));
      inData2 = static_cast<TTimingChargeData*>((*fInput)->UncheckedAt(2));
      id0 = inData0->GetID();
      id1 = inData1->GetID();
      id2 = inData2->GetID();
      c1 = inData1->GetCharge();
      c2 = inData2->GetCharge();
      if (TMath::IsNaN(c1) || TMath::IsNaN(c2)) return;

      pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + ((*fConverter)->Convert((c1 - c2)/(c1 + c2))) * ( id1 < id2 ? -1 : 1)  * 0.5 ) * fStripWidth  - fDetOffset);

   } else {
      return;
   }

   TSRPPACPlaneData *outData = static_cast<TSRPPACPlaneData*>(fOutput->ConstructedAt(0));
   outData->SetID(id0);
   outData->SetCharge(c0);
   outData->SetPosition(pos);
   outData->SetProcessed(kTRUE);
}