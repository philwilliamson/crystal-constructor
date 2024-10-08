export function buildSuperCell(crystal_model){
	// construct supercell model based on unit cell model and supercell multipliers
	crystal_model.super_cell.a_hat = [
        crystal_model.unit_cell.a_hat[0] * crystal_model.super_cell.a_hat_multiplier,
        crystal_model.unit_cell.a_hat[1] * crystal_model.super_cell.a_hat_multiplier,
        crystal_model.unit_cell.a_hat[2] * crystal_model.super_cell.a_hat_multiplier
    ];

	crystal_model.super_cell.b_hat = [
        crystal_model.unit_cell.b_hat[0] * crystal_model.super_cell.b_hat_multiplier,
        crystal_model.unit_cell.b_hat[1] * crystal_model.super_cell.b_hat_multiplier,
        crystal_model.unit_cell.b_hat[2] * crystal_model.super_cell.b_hat_multiplier
    ];

	crystal_model.super_cell.c_hat = [
        crystal_model.unit_cell.c_hat[0] * crystal_model.super_cell.c_hat_multiplier,
        crystal_model.unit_cell.c_hat[1] * crystal_model.super_cell.c_hat_multiplier,
        crystal_model.unit_cell.c_hat[2] * crystal_model.super_cell.c_hat_multiplier
    ];
	
	// create atom list for super cell
	crystal_model.super_cell.atoms = [];

	for (var k = 0; k < crystal_model.super_cell.c_hat_multiplier; k++){
		for (var j = 0; j < crystal_model.super_cell.b_hat_multiplier; j++){
			for (var i = 0; i < crystal_model.super_cell.a_hat_multiplier; i++){
				crystal_model.unit_cell.atoms.forEach(function(atom){
					var super_cell_atom = {
                        element: atom.element,
                        x_atom_pos: (atom.x_atom_pos + i) / crystal_model.super_cell.a_hat_multiplier,
                        y_atom_pos: (atom.y_atom_pos + j) / crystal_model.super_cell.b_hat_multiplier,
                        z_atom_pos: (atom.z_atom_pos + k) / crystal_model.super_cell.c_hat_multiplier
                    };
					crystal_model.super_cell.atoms.push(super_cell_atom);
				});
			}
		}
	}
	return crystal_model;
};

export function getElementColor(element){
	// get element color
	var defaultColor = [1, 0, 0, 1];

	if (element_colors.hasOwnProperty(element)) {
		return element_colors[element];
	}
	
	return defaultColor;
};

const element_colors = {
    "H": [1, 1, 1, 1],
    "He": [217/255, 1, 1, 1],
    "Li": [204/255, 128/255, 255/255, 1],
    "Be": [194/255, 255/255, 0/255, 1],
    "B": [255/255, 181/255, 181/255, 1],
    "C": [144/255, 144/255, 144/255, 1],
    "N": [48/255, 80/255, 248/255, 1],
    "O": [255/255, 13/255, 13/255, 1],
    "F": [144/255, 224/255, 80/255, 1],
    "Ne": [179/255, 227/255, 245/255, 1],
    "Na": [171/255, 92/255, 242/255, 1],
    "Mg": [138/255, 255/255, 0/255, 1],
    "Al": [191/255, 166/255, 166/255, 1],
    "Si": [240/255, 200/255, 160/255, 1],
    "P": [255/255, 128/255, 0/255, 1],
    "S": [255/255, 255/255, 48/255, 1],
    "Cl": [31/255, 240/255, 31/255, 1],
    "Ar": [128/255, 209/255, 227/255, 1],
    "K": [143/255, 64/255, 212/255, 1],
    "Ca": [61/255, 255/255, 0/255, 1],
    "Sc": [230/255, 230/255, 230/255, 1],
    "Ti": [191/255, 194/255, 199/255, 1],
    "V": [166/255, 166/255, 171/255, 1],
    "Cr": [138/255, 153/255, 199/255, 1],
    "Mn": [156/255, 122/255, 199/255, 1],
    "Fe": [224/255, 102/255, 51/255, 1],
    "Co": [240/255, 144/255, 160/255, 1],
    "Ni": [80/255, 208/255, 80/255, 1],
    "Cu": [200/255, 128/255, 51/255, 1],
    "Zn": [125/255, 128/255, 176/255, 1],
    "Ga": [194/255, 143/255, 143/255, 1],
    "Ge": [102/255, 143/255, 143/255, 1],
    "As": [189/255, 128/255, 227/255, 1],
    "Se": [255/255, 161/255, 0/255, 1],
    "Br": [166/255, 41/255, 41/255, 1],
    "Kr": [92/255, 184/255, 209/255, 1],
    "Rb": [112/255, 46/255, 176/255, 1],
    "Sr": [0/255, 255/255, 0/255, 1],
    "Y": [148/255, 255/255, 255/255, 1],
    "Zr": [148/255, 224/255, 224/255, 1],
    "Nb": [115/255, 194/255, 201/255, 1],
    "Mo": [84/255, 181/255, 181/255, 1],
    "Tc": [59/255, 158/255, 158/255, 1],
    "Ru": [36/255,143/255,143/255, 1],
    "Rh": [10/255,125/255,140/255, 1],
    "Pd": [0/255,105/255,133/255, 1],
    "Ag": [192/255,192/255,192/255, 1],
    "Cd": [255/255,217/255,143/255, 1],
    "In": [166/255,117/255,115/255, 1],
    "Sn": [102/255,128/255,128/255, 1],
    "Sb": [158/255,99/255,181/255, 1],
    "Te": [212/255,122/255,0/255, 1],
    "I": [148/255,0/255,148/255, 1],
    "Xe": [66/255,158/255,176/255, 1],
    "Cs": [87/255,23/255,143/255, 1],
    "Ba": [0/255,201/255,0/255, 1],
    "La": [112/255,212/255,255/255, 1],
    "Ce": [255/255,255/255,199/255, 1],
    "Pr": [217/255,255/255,199/255, 1],
    "Nd": [199/255,255/255,199/255, 1],
    "Pm": [163/255,255/255,199/255, 1],
    "Sm": [143/255,255/255,199/255, 1],
    "Eu": [97/255,255/255,199/255, 1],
    "Gd": [69/255,255/255,199/255, 1],
    "Tb": [48/255,255/255,199/255, 1],
    "Dy": [31/255,255/255,199/255, 1],
    "Ho": [0/255,255/255,156/255, 1],
    "Er": [0/255,230/255,117/255, 1],
    "Tm": [0/255,212/255,82/255, 1],
    "Yb": [0/255,191/255,56/255, 1],
    "Lu": [0/255,171/255,36/255, 1],
    "Hf": [77/255,194/255,255/255, 1],
    "Ta": [77/255,166/255,255/255, 1],
    "W": [33/255,148/255,214/255, 1],
    "Re": [38/255,125/255,171/255, 1],
    "Os": [38/255,102/255,150/255, 1],
    "Ir": [23/255,84/255,135/255, 1],
    "Pt": [208/255,208/255,224/255, 1],
    "Au": [255/255,209/255,35/255, 1],
    "Hg": [184/255,184/255,208/255, 1],
    "Tl": [166/255,84/255,77/255, 1],
    "Pb": [87/255,89/255,97/255, 1],
    "Bi": [158/255,79/255,181/255, 1],
    "Po": [171/255,92/255,0/255, 1],
    "At": [117/255,79/255,69/255, 1],
    "Rn": [66/255,130/255,150/255, 1],
    "Fr": [66/255,0/255,102/255, 1],
    "Ra": [0/255,125/255,0/255, 1],
    "Ac": [112/255,171/255,250/255, 1],
    "Th": [0/255,186/255,255/255, 1],
    "Pa": [0/255,161/255,255/255, 1],
    "U": [0/255,143/255,255/255, 1],
    "Np": [0/255,128/255,255/255, 1],
    "Pu": [0/255,107/255,255/255, 1],
    "Am": [84/255,92/255,242/255, 1],
    "Cm": [120/255,92/255,227/255, 1],
    "Bk": [138/255,79/255,227/255, 1],
    "Cf": [161/255,54/255,212/255, 1],
    "Es": [179/255,31/255,212/255, 1],
    "Fm": [179/255,31/255,186/255, 1],
    "Md": [179/255,13/255,166/255, 1],
    "No": [189/255,13/255,135/255, 1],
    "Lr": [199/255,0/255,102/255, 1],
    "Rf": [204/255,0/255,89/255, 1],
    "Db": [209/255,0/255,79/255, 1],
    "Sg": [217/255,0/255,69/255, 1],
    "Bh": [224/255,0/255,56/255, 1],
    "Hs": [230/255,0/255,46/255, 1],
    "Mt": [235/255,0/255,38/255, 1],
    "Ds": [240/255,0/255,28/255, 1],
    "Rg": [245/255,0/255,18/255, 1],
    "Cn": [250/255,0/255,8/255, 1],
    "Nh": [255/255,0/255,0/255, 1],
};