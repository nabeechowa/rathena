// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Script Commands
 * Place the body of custom script commands in this file.
 * Format:
 *	BUILDIN_FUNC(command_name)
 *	{
 *		<code>;
 *	}
 **/

//BUILDIN_FUNC(example)
//{
//	ShowInfo("buildin_example: It works!\n");
//	script_pushint(st,1);
//	return 0;
//}

BUILDIN_FUNC(unitisforcewalk)
{
	struct block_list *bl = nullptr;
	bool force_walk = false;

	if (script_getnum(st, 2))
		bl = map_id2bl(script_getnum(st,2));
	else
		bl = map_id2bl(st->rid);

	if (bl) {
		struct unit_data *ud = unit_bl2ud(bl);

		if (ud)
			force_walk = (ud->walktimer == INVALID_TIMER && ud->state.force_walk);
	}
	script_pushint(st, force_walk);

	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(isspawn)
{
	uint16 mob_ids[MAX_SEARCH] = {0};
	int count = 0;

	int mod_id;
	mod_id = script_getnum(st,2);
	if (mobdb_checkid(mod_id)) {
		mob_ids[0] = mod_id;
		count = 1;
	}

	if (count <= 0){
	push_val(st->stack,C_INT,false);
	return SCRIPT_CMD_SUCCESS;
	}

	if (count >= MAX_SEARCH)
	count = MAX_SEARCH;

	for (int i = 0; i < count; i++) {
		uint16 mob_id = mob_ids[i];
		std::shared_ptr<s_mob_db> mob = mob_db.find(mob_id);

		if(!mob)
		continue;

		const std::vector<spawn_info> spawns = mob_get_spawns(mob_id);
		if (spawns.size() <= 0){
		push_val(st->stack,C_INT,false);
		return SCRIPT_CMD_SUCCESS;
		}
		else {
			for(auto& spawn : spawns){
				int16 mapid = map_mapindex2mapid(spawn.mapindex);
				if (mapid < 0)
					continue;
					push_val(st->stack,C_INT,true);
					return SCRIPT_CMD_SUCCESS;
			}
		}
	}

	push_val(st->stack,C_INT,false);
	return SCRIPT_CMD_SUCCESS;
}

/*
    fakeplayerzxc( map, x, y, name, job_id, sex, hair_style, hair_color, weapon, shield, head_top, head_mid, head_bottom, option, cloth_color );
    Returns the GID
*/
 BUILDIN_FUNC(fakeplayerzxc)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m;
     struct mob_data* md = nullptr;
 
     m = map_mapname2mapid(mapn);
 
	 // Using poring as monster behavior
     md = mob_once_spawn_sub(NULL, m, x, y, name, 31000, "", SZ_SMALL, AI_NONE);
 
     if (!md)
         return SCRIPT_CMD_FAILURE;
 
     md->ud.immune_attack = 1;

     md->vd->class_ = sprite;

     md->vd->sex = sex;
     md->vd->hair_style = hair_style;
     md->vd->hair_color = hair_color;
     md->vd->weapon = weapon;
     md->vd->shield = shield;
     md->vd->head_top = head_top;
     md->vd->head_mid = head_mid;
     md->vd->head_bottom = head_bottom;
     md->vd->cloth_color = cloth_color;
 
     mob_spawn(md);
     script_pushint(st, md->bl.id);
     return SCRIPT_CMD_SUCCESS;
 }
 BUILDIN_FUNC(fakeplayerzxc1)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m1;
     struct mob_data* md1 = nullptr;
 
     m1 = map_mapname2mapid(mapn);

	 md1 = mob_once_spawn_sub(NULL, m1, x, y, name, 31001, "", SZ_SMALL, AI_NONE);

     if (!md1)
         return SCRIPT_CMD_FAILURE;
	 
     md1->ud.immune_attack = 1;

     md1->vd->class_ = sprite;

     md1->vd->sex = sex;
     md1->vd->hair_style = hair_style;
     md1->vd->hair_color = hair_color;
     md1->vd->weapon = weapon;
     md1->vd->shield = shield;
     md1->vd->head_top = head_top;
     md1->vd->head_mid = head_mid;
     md1->vd->head_bottom = head_bottom;
     md1->vd->cloth_color = cloth_color;

      mob_spawn(md1);
     script_pushint(st, md1->bl.id);
     return SCRIPT_CMD_SUCCESS;
}
 BUILDIN_FUNC(fakeplayerzxc2)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m2;
     struct mob_data* md2 = nullptr;
 
     m2 = map_mapname2mapid(mapn);
	 
	 md2 = mob_once_spawn_sub(NULL, m2, x, y, name, 31002, "", SZ_SMALL, AI_NONE);

     if (!md2)
         return SCRIPT_CMD_FAILURE;
	 
     md2->ud.immune_attack = 1;

     md2->vd->class_ = sprite;

     md2->vd->sex = sex;
     md2->vd->hair_style = hair_style;
     md2->vd->hair_color = hair_color;
     md2->vd->weapon = weapon;
     md2->vd->shield = shield;
     md2->vd->head_top = head_top;
     md2->vd->head_mid = head_mid;
     md2->vd->head_bottom = head_bottom;
     md2->vd->cloth_color = cloth_color;

     mob_spawn(md2);
     script_pushint(st, md2->bl.id);
     return SCRIPT_CMD_SUCCESS;
}
 BUILDIN_FUNC(fakeplayerzxc3)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m3;
     struct mob_data* md3 = nullptr;
 
     m3 = map_mapname2mapid(mapn);

	 md3 = mob_once_spawn_sub(NULL, m3, x, y, name, 31003, "", SZ_SMALL, AI_NONE);

     if (!md3)
         return SCRIPT_CMD_FAILURE;
	 
     md3->ud.immune_attack = 1;

     md3->vd->class_ = sprite;

     md3->vd->sex = sex;
     md3->vd->hair_style = hair_style;
     md3->vd->hair_color = hair_color;
     md3->vd->weapon = weapon;
     md3->vd->shield = shield;
     md3->vd->head_top = head_top;
     md3->vd->head_mid = head_mid;
     md3->vd->head_bottom = head_bottom;
     md3->vd->cloth_color = cloth_color;

     mob_spawn(md3);
     script_pushint(st, md3->bl.id);
     return SCRIPT_CMD_SUCCESS;
}
 BUILDIN_FUNC(fakeplayerzxc4)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m4;
     struct mob_data* md4 = nullptr;
 
     m4 = map_mapname2mapid(mapn);

	 md4 = mob_once_spawn_sub(NULL, m4, x, y, name, 31004, "", SZ_SMALL, AI_NONE);

     if (!md4)
         return SCRIPT_CMD_FAILURE;
	 
     md4->ud.immune_attack = 1;

     md4->vd->class_ = sprite;

     md4->vd->sex = sex;
     md4->vd->hair_style = hair_style;
     md4->vd->hair_color = hair_color;
     md4->vd->weapon = weapon;
     md4->vd->shield = shield;
     md4->vd->head_top = head_top;
     md4->vd->head_mid = head_mid;
     md4->vd->head_bottom = head_bottom;
     md4->vd->cloth_color = cloth_color;

     mob_spawn(md4);
     script_pushint(st, md4->bl.id);
     return SCRIPT_CMD_SUCCESS;
}
 BUILDIN_FUNC(fakeplayerzxc5)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m5;
     struct mob_data* md5 = nullptr;
 
     m5 = map_mapname2mapid(mapn);

	 md5 = mob_once_spawn_sub(NULL, m5, x, y, name, 31005, "", SZ_SMALL, AI_NONE);

     if (!md5)
         return SCRIPT_CMD_FAILURE;
	 
     md5->ud.immune_attack = 1;

     md5->vd->class_ = sprite;

     md5->vd->sex = sex;
     md5->vd->hair_style = hair_style;
     md5->vd->hair_color = hair_color;
     md5->vd->weapon = weapon;
     md5->vd->shield = shield;
     md5->vd->head_top = head_top;
     md5->vd->head_mid = head_mid;
     md5->vd->head_bottom = head_bottom;
     md5->vd->cloth_color = cloth_color;

     mob_spawn(md5);
     script_pushint(st, md5->bl.id);
     return SCRIPT_CMD_SUCCESS;
}
 BUILDIN_FUNC(fakeplayerzxc6)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m6;
     struct mob_data* md6 = nullptr;
 
     m6 = map_mapname2mapid(mapn);

	 md6 = mob_once_spawn_sub(NULL, m6, x, y, name, 31006, "", SZ_SMALL, AI_NONE);

     if (!md6)
         return SCRIPT_CMD_FAILURE;
	 
     md6->ud.immune_attack = 1;

     md6->vd->class_ = sprite;

     md6->vd->sex = sex;
     md6->vd->hair_style = hair_style;
     md6->vd->hair_color = hair_color;
     md6->vd->weapon = weapon;
     md6->vd->shield = shield;
     md6->vd->head_top = head_top;
     md6->vd->head_mid = head_mid;
     md6->vd->head_bottom = head_bottom;
     md6->vd->cloth_color = cloth_color;

     mob_spawn(md6);
     script_pushint(st, md6->bl.id);
     return SCRIPT_CMD_SUCCESS;
}
 BUILDIN_FUNC(fakeplayerzxc7)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m7;
     struct mob_data* md7 = nullptr;
 
     m7 = map_mapname2mapid(mapn);

	 md7 = mob_once_spawn_sub(NULL, m7, x, y, name, 31007, "", SZ_SMALL, AI_NONE);

     if (!md7)
         return SCRIPT_CMD_FAILURE;
	 
     md7->ud.immune_attack = 1;

     md7->vd->class_ = sprite;

     md7->vd->sex = sex;
     md7->vd->hair_style = hair_style;
     md7->vd->hair_color = hair_color;
     md7->vd->weapon = weapon;
     md7->vd->shield = shield;
     md7->vd->head_top = head_top;
     md7->vd->head_mid = head_mid;
     md7->vd->head_bottom = head_bottom;
     md7->vd->cloth_color = cloth_color;

     mob_spawn(md7);
     script_pushint(st, md7->bl.id);
     return SCRIPT_CMD_SUCCESS;
}
 BUILDIN_FUNC(fakeplayerzxc8)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m8;
     struct mob_data* md8 = nullptr;
 
     m8 = map_mapname2mapid(mapn);

	 md8 = mob_once_spawn_sub(NULL, m8, x, y, name, 31008, "", SZ_SMALL, AI_NONE);

     if (!md8)
         return SCRIPT_CMD_FAILURE;
	 
     md8->ud.immune_attack = 1;

     md8->vd->class_ = sprite;

     md8->vd->sex = sex;
     md8->vd->hair_style = hair_style;
     md8->vd->hair_color = hair_color;
     md8->vd->weapon = weapon;
     md8->vd->shield = shield;
     md8->vd->head_top = head_top;
     md8->vd->head_mid = head_mid;
     md8->vd->head_bottom = head_bottom;
     md8->vd->cloth_color = cloth_color;

     mob_spawn(md8);
     script_pushint(st, md8->bl.id);
     return SCRIPT_CMD_SUCCESS;
}
 BUILDIN_FUNC(fakeplayerzxc9)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m9;
     struct mob_data* md9 = nullptr;
 
     m9 = map_mapname2mapid(mapn);

	 md9 = mob_once_spawn_sub(NULL, m9, x, y, name, 31009, "", SZ_SMALL, AI_NONE);

     if (!md9)
         return SCRIPT_CMD_FAILURE;
	 
     md9->ud.immune_attack = 1;

     md9->vd->class_ = sprite;

     md9->vd->sex = sex;
     md9->vd->hair_style = hair_style;
     md9->vd->hair_color = hair_color;
     md9->vd->weapon = weapon;
     md9->vd->shield = shield;
     md9->vd->head_top = head_top;
     md9->vd->head_mid = head_mid;
     md9->vd->head_bottom = head_bottom;
     md9->vd->cloth_color = cloth_color;

     mob_spawn(md9);
     script_pushint(st, md9->bl.id);
     return SCRIPT_CMD_SUCCESS;
}
 BUILDIN_FUNC(fakeplayerzxc10)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m10;
     struct mob_data* md10 = nullptr;
 
     m10 = map_mapname2mapid(mapn);

	 md10 = mob_once_spawn_sub(NULL, m10, x, y, name, 31010, "", SZ_SMALL, AI_NONE);

     if (!md10)
         return SCRIPT_CMD_FAILURE;
	 
     md10->ud.immune_attack = 1;

     md10->vd->class_ = sprite;

     md10->vd->sex = sex;
     md10->vd->hair_style = hair_style;
     md10->vd->hair_color = hair_color;
     md10->vd->weapon = weapon;
     md10->vd->shield = shield;
     md10->vd->head_top = head_top;
     md10->vd->head_mid = head_mid;
     md10->vd->head_bottom = head_bottom;
     md10->vd->cloth_color = cloth_color;

     mob_spawn(md10);
     script_pushint(st, md10->bl.id);
     return SCRIPT_CMD_SUCCESS;
}
 BUILDIN_FUNC(fakeplayerzxc11)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m11;
     struct mob_data* md11 = nullptr;
 
     m11 = map_mapname2mapid(mapn);

	 md11 = mob_once_spawn_sub(NULL, m11, x, y, name, 31011, "", SZ_SMALL, AI_NONE);

     if (!md11)
         return SCRIPT_CMD_FAILURE;
	 
     md11->ud.immune_attack = 1;

     md11->vd->class_ = sprite;

     md11->vd->sex = sex;
     md11->vd->hair_style = hair_style;
     md11->vd->hair_color = hair_color;
     md11->vd->weapon = weapon;
     md11->vd->shield = shield;
     md11->vd->head_top = head_top;
     md11->vd->head_mid = head_mid;
     md11->vd->head_bottom = head_bottom;
     md11->vd->cloth_color = cloth_color;

     mob_spawn(md11);
     script_pushint(st, md11->bl.id);
     return SCRIPT_CMD_SUCCESS;
}
 BUILDIN_FUNC(fakeplayerzxc12)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m12;
     struct mob_data* md12 = nullptr;
 
     m12 = map_mapname2mapid(mapn);

	 md12 = mob_once_spawn_sub(NULL, m12, x, y, name, 31012, "", SZ_SMALL, AI_NONE);

     if (!md12)
         return SCRIPT_CMD_FAILURE;
	 
     md12->ud.immune_attack = 1;

     md12->vd->class_ = sprite;

     md12->vd->sex = sex;
     md12->vd->hair_style = hair_style;
     md12->vd->hair_color = hair_color;
     md12->vd->weapon = weapon;
     md12->vd->shield = shield;
     md12->vd->head_top = head_top;
     md12->vd->head_mid = head_mid;
     md12->vd->head_bottom = head_bottom;
     md12->vd->cloth_color = cloth_color;

     mob_spawn(md12);
     script_pushint(st, md12->bl.id);
     return SCRIPT_CMD_SUCCESS;
}
 BUILDIN_FUNC(fakeplayerzxc13)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m13;
     struct mob_data* md13 = nullptr;
 
     m13 = map_mapname2mapid(mapn);

	 md13 = mob_once_spawn_sub(NULL, m13, x, y, name, 31013, "", SZ_SMALL, AI_NONE);

     if (!md13)
         return SCRIPT_CMD_FAILURE;
	 
     md13->ud.immune_attack = 1;

     md13->vd->class_ = sprite;

     md13->vd->sex = sex;
     md13->vd->hair_style = hair_style;
     md13->vd->hair_color = hair_color;
     md13->vd->weapon = weapon;
     md13->vd->shield = shield;
     md13->vd->head_top = head_top;
     md13->vd->head_mid = head_mid;
     md13->vd->head_bottom = head_bottom;
     md13->vd->cloth_color = cloth_color;

     mob_spawn(md13);
     script_pushint(st, md13->bl.id);
     return SCRIPT_CMD_SUCCESS;
}
 BUILDIN_FUNC(fakeplayerzxc14)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m14;
     struct mob_data* md14 = nullptr;
 
     m14 = map_mapname2mapid(mapn);

	 md14 = mob_once_spawn_sub(NULL, m14, x, y, name, 31014, "", SZ_SMALL, AI_NONE);

     if (!md14)
         return SCRIPT_CMD_FAILURE;
	 
     md14->ud.immune_attack = 1;

     md14->vd->class_ = sprite;

     md14->vd->sex = sex;
     md14->vd->hair_style = hair_style;
     md14->vd->hair_color = hair_color;
     md14->vd->weapon = weapon;
     md14->vd->shield = shield;
     md14->vd->head_top = head_top;
     md14->vd->head_mid = head_mid;
     md14->vd->head_bottom = head_bottom;
     md14->vd->cloth_color = cloth_color;

     mob_spawn(md14);
     script_pushint(st, md14->bl.id);
     return SCRIPT_CMD_SUCCESS;
}
 BUILDIN_FUNC(fakeplayerzxc15)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m15;
     struct mob_data* md15 = nullptr;
 
     m15 = map_mapname2mapid(mapn);

	 md15 = mob_once_spawn_sub(NULL, m15, x, y, name, 31015, "", SZ_SMALL, AI_NONE);

     if (!md15)
         return SCRIPT_CMD_FAILURE;
	 
     md15->ud.immune_attack = 1;

     md15->vd->class_ = sprite;

     md15->vd->sex = sex;
     md15->vd->hair_style = hair_style;
     md15->vd->hair_color = hair_color;
     md15->vd->weapon = weapon;
     md15->vd->shield = shield;
     md15->vd->head_top = head_top;
     md15->vd->head_mid = head_mid;
     md15->vd->head_bottom = head_bottom;
     md15->vd->cloth_color = cloth_color;

     mob_spawn(md15);
     script_pushint(st, md15->bl.id);
     return SCRIPT_CMD_SUCCESS;
}
 BUILDIN_FUNC(fakeplayerzxc16)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m16;
     struct mob_data* md16 = nullptr;
 
     m16 = map_mapname2mapid(mapn);

	 md16 = mob_once_spawn_sub(NULL, m16, x, y, name, 31016, "", SZ_SMALL, AI_NONE);

     if (!md16)
         return SCRIPT_CMD_FAILURE;
	 
     md16->ud.immune_attack = 1;

     md16->vd->class_ = sprite;

     md16->vd->sex = sex;
     md16->vd->hair_style = hair_style;
     md16->vd->hair_color = hair_color;
     md16->vd->weapon = weapon;
     md16->vd->shield = shield;
     md16->vd->head_top = head_top;
     md16->vd->head_mid = head_mid;
     md16->vd->head_bottom = head_bottom;
     md16->vd->cloth_color = cloth_color;

     mob_spawn(md16);
     script_pushint(st, md16->bl.id);
     return SCRIPT_CMD_SUCCESS;
}
 BUILDIN_FUNC(fakeplayerzxc17)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m17;
     struct mob_data* md17 = nullptr;
 
     m17 = map_mapname2mapid(mapn);

	 md17 = mob_once_spawn_sub(NULL, m17, x, y, name, 31017, "", SZ_SMALL, AI_NONE);

     if (!md17)
         return SCRIPT_CMD_FAILURE;
	 
     md17->ud.immune_attack = 1;

     md17->vd->class_ = sprite;
 
     md17->vd->sex = sex;
     md17->vd->hair_style = hair_style;
     md17->vd->hair_color = hair_color;
     md17->vd->weapon = weapon;
     md17->vd->shield = shield;
     md17->vd->head_top = head_top;
     md17->vd->head_mid = head_mid;
     md17->vd->head_bottom = head_bottom;
     md17->vd->cloth_color = cloth_color;

     mob_spawn(md17);
     script_pushint(st, md17->bl.id);
     return SCRIPT_CMD_SUCCESS;
}
 BUILDIN_FUNC(fakeplayerzxc18)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m18;
     struct mob_data* md18 = nullptr;
 
     m18 = map_mapname2mapid(mapn);

	 md18 = mob_once_spawn_sub(NULL, m18, x, y, name, 31018, "", SZ_SMALL, AI_NONE);

     if (!md18)
         return SCRIPT_CMD_FAILURE;

     md18->ud.immune_attack = 1;

     md18->vd->class_ = sprite;
 
     md18->vd->sex = sex;
     md18->vd->hair_style = hair_style;
     md18->vd->hair_color = hair_color;
     md18->vd->weapon = weapon;
     md18->vd->shield = shield;
     md18->vd->head_top = head_top;
     md18->vd->head_mid = head_mid;
     md18->vd->head_bottom = head_bottom;
     md18->vd->cloth_color = cloth_color;

     mob_spawn(md18);
     script_pushint(st, md18->bl.id);
     return SCRIPT_CMD_SUCCESS;
}
 BUILDIN_FUNC(fakeplayerzxc19)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m19;
     struct mob_data* md19 = nullptr;
 
     m19 = map_mapname2mapid(mapn);

	 md19 = mob_once_spawn_sub(NULL, m19, x, y, name, 31019, "", SZ_SMALL, AI_NONE);

     if (!md19)
         return SCRIPT_CMD_FAILURE;
	 
     md19->ud.immune_attack = 1;

     md19->vd->class_ = sprite;

     md19->vd->sex = sex;
     md19->vd->hair_style = hair_style;
     md19->vd->hair_color = hair_color;
     md19->vd->weapon = weapon;
     md19->vd->shield = shield;
     md19->vd->head_top = head_top;
     md19->vd->head_mid = head_mid;
     md19->vd->head_bottom = head_bottom;
     md19->vd->cloth_color = cloth_color;

     mob_spawn(md19);
     script_pushint(st, md19->bl.id);
     return SCRIPT_CMD_SUCCESS;
}
 BUILDIN_FUNC(fakeplayerzxc20)
 {
     const char* mapn = script_getstr(st, 2);
     int x = script_getnum(st, 3);
     int y = script_getnum(st, 4);
 
     const char* name = script_getstr(st, 5);
     int sprite = script_getnum(st, 6);
     int sex = script_getnum(st, 7);
     int hair_style = script_getnum(st, 8);
     int hair_color = script_getnum(st, 9);
     int weapon = script_getnum(st, 10);
     int shield = script_getnum(st, 11);
     int head_top = script_getnum(st, 12);
     int head_mid = script_getnum(st, 13);
     int head_bottom = script_getnum(st, 14);
     int option = script_getnum(st, 15);
     int cloth_color = script_getnum(st, 16);
 
     int16 m20;
     struct mob_data* md20 = nullptr;
 
     m20 = map_mapname2mapid(mapn);

	 md20 = mob_once_spawn_sub(NULL, m20, x, y, name, 31020, "", SZ_SMALL, AI_NONE);

     if (!md20)
         return SCRIPT_CMD_FAILURE;

     md20->ud.immune_attack = 1;

     md20->vd->class_ = sprite;

     md20->vd->sex = sex;
     md20->vd->hair_style = hair_style;
     md20->vd->hair_color = hair_color;
     md20->vd->weapon = weapon;
     md20->vd->shield = shield;
     md20->vd->head_top = head_top;
     md20->vd->head_mid = head_mid;
     md20->vd->head_bottom = head_bottom;
     md20->vd->cloth_color = cloth_color;

     mob_spawn(md20);
     script_pushint(st, md20->bl.id);
     return SCRIPT_CMD_SUCCESS;
}