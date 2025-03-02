
#include "zxsrxt_helpers.hpp"



class c_vars_t {
public:
bool p_players = {};
bool p_box = {};
bool p_name = {};
bool p_skeletone = {};
bool p_aim = {};
int aim_fov = {oxorany(60)};
bool p_chams = {};
};
c_vars_t* c_vars = new c_vars_t();




class game_sdk_t{

public:
    void init();
    Vector3(*get_position)(uintptr_t);
    uintptr_t(*get_transform)(uintptr_t);
    uintptr_t(*camera)();
    Vector3(*world_to_viewport)(uintptr_t, Vector3);
    void(*set_visible)(uintptr_t, bool);
    void(*set_enabled)(uintptr_t, bool);
    ImVec2 w_regular(Vector3);
    ImVec2 w_checker(Vector3, bool&);
};
game_sdk_t* game_sdk = new game_sdk_t();

void game_sdk_t::init(){
    this->get_position = reinterpret_cast<Vector3 (*)(uintptr_t)>(
      base_addr + oxorany(0x5620840)
    );
    this->get_transform = reinterpret_cast<uintptr_t (*)(uintptr_t)>(
      base_addr + oxorany(0x5610C90)
    );
    this->camera = reinterpret_cast<uintptr_t (*)()>(
      base_addr + oxorany(0x55D8D04)
    );
    this->world_to_viewport = reinterpret_cast<Vector3 (*)(uintptr_t, Vector3)>(
      base_addr + oxorany(0x55D83D4)
    );

    this->set_visible =
    reinterpret_cast<void (*)(uintptr_t, bool)>(
       base_addr + oxorany(0x2B976A8)
     );
    this->set_enabled =
    reinterpret_cast<void (*)(uintptr_t, bool)>(
       base_addr + oxorany(0x2B97494)
     );
}


ImVec2 game_sdk_t::w_regular(Vector3 pos) {

auto cam = game_sdk->camera();
if(!cam)return {oxorany(0),oxorany(0)};

        Vector3 worldPoint = game_sdk->world_to_viewport(cam, pos);
        Vector3 location;
        int ScreenWidth = ImGui::GetIO().DisplaySize.x;
        int ScreenHeight = ImGui::GetIO().DisplaySize.y;
        location.x = ScreenWidth * worldPoint.x;
        location.y = ScreenHeight - worldPoint.y * ScreenHeight;
        location.z = worldPoint.z;
        return {location.x, location.y};
    }
    ImVec2 game_sdk_t::w_checker(Vector3 pos, bool &checker) {

        auto cam = game_sdk->camera();
if(!cam)return {oxorany(0),oxorany(0)};

        Vector3 worldPoint = game_sdk->world_to_viewport(cam, pos);
        Vector3 location;
        int ScreenWidth = ImGui::GetIO().DisplaySize.x;
        int ScreenHeight = ImGui::GetIO().DisplaySize.y;
        location.x = ScreenWidth * worldPoint.x;
        location.y = ScreenHeight - worldPoint.y * ScreenHeight;
        location.z = worldPoint.z;
        checker = location.z > oxorany(1);
        return {location.x, location.y};
    }
Vector3 camera_pos = {};
inline bool linecast(Vector3 end){
  static auto lncst = reinterpret_cast<bool (*)(Vector3, Vector3, int)>(
    getRealOffset(oxorany(0x568EC74))
  );
  return lncst(camera_pos, end, oxorany(16384));
}

bool if_fov(ImVec2 vec1, ImVec2 vec2, int radius) {
	if ((pow(vec1.x - vec2.x, oxorany(2)) + pow(vec1.y - vec2.y, oxorany(2))) <= pow(radius, oxorany(2))) {
		return true;
	}
	else {
		return false;
	}
}

inline bool infov(ImVec2 pos) {
    return if_fov(ImGui::GetIO().DisplaySize / 2, pos, c_vars->aim_fov);
}
namespace shoot {
  Vector3 pos;
  bool can;
}

inline auto bone_v2(uintptr_t target, uintptr_t off) -> ImVec2 {
  const auto& bipedmap = *reinterpret_cast<uintptr_t*>(*reinterpret_cast<uintptr_t*>(target + oxorany(0xA8)) + oxorany(0x58));
  const auto& bone = *reinterpret_cast<uintptr_t*>(bipedmap + off);
  return game_sdk->w_regular(game_sdk->get_position(bone));
}

std::vector<uintptr_t> vec = {};
uintptr_t local = {};
inline void renderesp(){
	std::vector<std::string> keys = {
	 oxorany("bt_sjfn27wx42x894ir"),
	 oxorany("bt_bw5cy42yac2zabko"),
	 oxorany("bt_xcdhxkbqso0z7xnp"),
	 oxorany("bt_vsalrmx9eve4drv0"),
	 oxorany("bt_ud7nfvpz7xq2w6ih"),
	 oxorany("bt_zzclw3oa2v2ozxww"),
	 oxorany("bt_15mgiaflzmkwo8mp"),
	 oxorany("bt_kdkt4ij63ckrxpyh"),
	 oxorany("bt_yn9lzshzn2mdxz5e"),
	 oxorany("bt_han143upyischrm6"),
	 oxorany("bt_gt306znyc2e4169n"),
	 oxorany("bt_r8ljx726f7ta0jww"),
	 oxorany("bt_7lukw36eouervxam"),
	 oxorany("bt_kupuoywybieippk0"),
	 oxorany("bt_h6toldy7mbbg21qn"),
	 oxorany("bt_ig2ko3a8y4xjoi2x"),
	 oxorany("bt_sg8ryw1jv3d87srz"),
	 oxorany("bt_6m4mlysle797qkdr"),
	 oxorany("bt_5y42izh1qen1zqva"),
	 oxorany("bt_b3cr5aesl2wujwec"),
	 oxorany("bt_gfrzyfaannzinvgn"),
	 oxorany("bt_ym1ksq5vjytg1zl1"),
	 oxorany("bt_kzh6wiq13hbm7dnf"),
	 oxorany("bt_i18wajqmmrqc5zum"),
	 oxorany("bt_kqyuftzrkoc4xq52"),
	 oxorany("bt_xmo9obv4oyht4yp7"),
	 oxorany("bt_lky4fpb35pminxea"),
	 oxorany("bt_082vc4sn0e9bav2h"),
	 oxorany("bt_3uljd9bmvu0asxuh"),
	 oxorany("bt_tu5mqkdh8us596ff"),
	 oxorany("bt_o744w1rn41o5hstb"),
	 oxorany("bt_ylihcoifogtpt7nn"),
	 oxorany("bt_dpj3c4nga5gkph09"),
	 oxorany("bt_j444ch46brb2x6hy"),
	 oxorany("bt_rou0yf8ewkmxwk7r"),
	 oxorany("bt_953du7f16vl3l3xo"),
	 oxorany("bt_7lswlbuw4qjge2e2"),
	 oxorany("bt_3k23oywk65x9g0ef"),
	 oxorany("bt_wq2mletjhk7k1orh"),
	 oxorany("bt_zzerof914e29nq7y"),
	 oxorany("bt_nptjeu13mgaedtb5"),
	 oxorany("bt_t2qw0s9s4iu7dtnr"),
	 oxorany("bt_41n0hibys6m23gw0"),
	 oxorany("bt_w4xc1lw3aewtui7j"),
	 oxorany("bt_7qspua3npqfql6fl"),
	 oxorany("bt_4rezo3844vq6uy8d"),
	 oxorany("bt_qf17fu5os0xgx2zr"),
	 oxorany("bt_3ebmpbu776eo7n03"),
	 oxorany("bt_iz8qem4eidkwjmqc"),
	 oxorany("bt_h030fka2ktm9h7ip"),
	 oxorany("bt_nmdh3ip1m3km00e9"),
	 oxorany("bt_6m9rvxd11t46bogn"),
	 oxorany("bt_ss2947rjo1gpqjka"),
	 oxorany("bt_tzxlw7rkmjlgpf54"),
	 oxorany("bt_2208enga9rieqasj"),
	 oxorany("bt_27xinwm6z78cil3m"),
	 oxorany("bt_e0ztqrmmrzg5aw3a"),
	 oxorany("bt_7hjv36h3qlfaugpc"),
	 oxorany("bt_o1we5r4a5g7stf2g"),
	 oxorany("bt_nz0kvjno43bu7y45"),
	 oxorany("bt_3qzc3w5418qx4tr0"),
	 oxorany("bt_58lsu56yr914d7ur"),
	 oxorany("bt_hredyctdxyfwkxuo"),
	 oxorany("bt_ljgvp3bx0bu3r1ns"),
	 oxorany("bt_zcjxgdurp7gdh4zt"),
	 oxorany("bt_jqmf7vk56zdmk47c"),
	 oxorany("bt_i88xu6j35suj2rid"),
	 oxorany("bt_tgm61h71jsd1ptrm"),
	 oxorany("bt_ae3giq8tse2zt23k"),
	 oxorany("bt_9ha1grb2sud9qdhf"),
	 oxorany("bt_hzwc4486vq0scd0h"),
	 oxorany("bt_n0kdxkwqbh3d2nqv"),
	 oxorany("bt_69ti71j2lfd8ynlh"),
	 oxorany("bt_asx4fal9dd14kk92"),
	 oxorany("bt_d19g3pzi554fvbvj"),
	 oxorany("bt_tblgr5aqw3bvuakh"),
	 oxorany("bt_iqranijwa4pd9tn5"),
	 oxorany("bt_hcfw1ejhq17lbix0"),
	 oxorany("bt_8w1k0fmemz5kkt5w"),
	 oxorany("bt_d5pxyk8k8kr1wgdy"),
	 oxorany("bt_chrsp1qphsc7kssq"),
	 oxorany("bt_0gxklab5e5wpctib"),
	 oxorany("bt_7depe2hoqe91uwt3"),
	 oxorany("bt_a3sn39fdzmyk4zeu"),
	 oxorany("bt_8coh63kwtda59f52"),
	 oxorany("bt_4k3ywvjueo2zasb4"),
	 oxorany("bt_a3kohf3k7d1mmjdz"),
	 oxorany("bt_w54prlnnog66gmpz"),
	 oxorany("bt_o4bwapdhm7v0eqg5"),
	 oxorany("bt_egur5nyizhd92rya"),
	 oxorany("bt_j4x357rqw94muyxm"),
	 oxorany("bt_ozpo7qd5aimtmxdr"),
	 oxorany("bt_afapsztgdwc6e2vo"),
	 oxorany("bt_ycate1ccax9rim0i"),
	 oxorany("bt_6htm6pjf4s2x57vw"),
	 oxorany("bt_xteeejrrhl4zldn2"),
	 oxorany("bt_l3o9j7hmk0km36pq"),
	 oxorany("bt_wt539hiwiy8s17v3"),
	 oxorany("bt_6zh0814qgkr0fylj"),
	 oxorany("bt_4kqyj550u1o8itcd"),
	 oxorany("bt_6it6smseprzms6iv"),
	 oxorany("bt_ya369fz71z6nra58"),
	 oxorany("bt_y69d3ktf65rkwqip"),
	 oxorany("bt_a8awa6ld1b8d4xt8"),
	 oxorany("bt_zr2000355xx1f0fi"),
	 oxorany("bt_ubo76crrysi6bqwy"),
	 oxorany("bt_wrawuvfmw1r0p3y6"),
	 oxorany("bt_rncw7rprzmua320k"),
	 oxorany("bt_yn6rs0spfo8wr6zr"),
	 oxorany("bt_jdcm5eemier2w7sg"),
	 oxorany("bt_5m8254wcw0jl1mek"),
	 oxorany("bt_93rfnl4f8a9lmylv"),
	 oxorany("bt_ikknptxgs44z1aqb"),
	 oxorany("bt_qzgk4cp544u44n8w"),
	 oxorany("bt_g01pjjdo3yp7sz66"),
	 oxorany("bt_z71o01utpmhuof8o"),
	 oxorany("bt_blaymaht3awj8blp"),
	 oxorany("bt_ld4g1beflexvbsxf"),
	 oxorany("bt_awfuvw1e544idcnj"),
	 oxorany("bt_wepnoejyweayyoto"),
	 oxorany("bt_m3zuhm1cltvargap"),
	 oxorany("bt_mbdu32kx0sr7xdnz"),
	 oxorany("bt_qnau9xbugs5s1p1t"),
	 oxorany("bt_t85906shkbyfetum"),
	 oxorany("bt_q4wlhzehmwtco2zb"),
	 oxorany("bt_k2zqdg9tmaha4bwy"),
	 oxorany("bt_er6ozapttakxkbws"),
	 oxorany("bt_wrc9fogymbxzraf6"),
	 oxorany("bt_f0gr7kk2wcjb8nfk"),
	 oxorany("bt_scfhqjvfohtqn5cb"),
	 oxorany("bt_wi7h8j475fbnhpoa"),
	 oxorany("bt_k9ei7jjpccrdegqo"),
	 oxorany("bt_28fytplzn1kl3cj7"),
	 oxorany("bt_sffq18m1rspbkyj8"),
	 oxorany("bt_47zzocfdcqq5njbe"),
	 oxorany("bt_6dcujz0v56walih1"),
	 oxorany("bt_lpyspfdbn1pt8ntz"),
	 oxorany("bt_avjev8wnwb5imc61"),
	 oxorany("bt_4vjsvqn3k1objdlo"),
	 oxorany("bt_ob960inj3nhhqlbz"),
	 oxorany("bt_ynbwut2iwhg4y6nz"),
	 oxorany("bt_aa64juusej8gufrg"),
	 oxorany("bt_2r7fqwqanbxx1nz9"),
	 oxorany("bt_w1wxsmkh1kdmk4xs"),
	 oxorany("bt_kewmsbgvfpnc65k5"),
	 oxorany("bt_muvzpjmr0zo5yi1y"),
	 oxorany("bt_z9lh8utcexycaycv"),
	 oxorany("bt_t7wkofke1uo09mp8"),
	 oxorany("bt_b09nktiu872eeep1"),
	 oxorany("bt_c7ch9rml0n049ogm"),
	 oxorany("bt_vpnottu14wh3hpko"),
	 oxorany("bt_89qdlrk10gvi1xl6"),
	 oxorany("bt_9c9ppkr81wzf53t3"),
	 oxorany("bt_v35pwwtlz4d41ksp"),
	 oxorany("bt_9vs7hzr7kc9a3oj8"),
	 oxorany("bt_uv10wk30zvhiissw"),
	 oxorany("bt_msfafnfeb2nbjdje"),
	 oxorany("bt_8jnct9r86spyw8q3"),
	 oxorany("bt_jccyyuj4wf8xnc7k"),
	 oxorany("bt_j2071p1omiyc31e7"),
	 oxorany("bt_h45quibsfn8ond7p"),
	 oxorany("bt_94ih9mprl18838sx"),
	 oxorany("bt_jasd5xbmw4kxz8bk"),
	 oxorany("bt_hwu3pi67rsmkycoy"),
	 oxorany("bt_p8ive2m1sxuwpo4a"),
	 oxorany("bt_rokk1nq2vtlm6fhe"),
	 oxorany("bt_w576j62zmj69nroa"),
	 oxorany("bt_28xog9yahsxus1ph"),
	 oxorany("bt_roubgpwmqnomwtkd"),
	 oxorany("bt_vepp6t3uxza10nqq"),
	 oxorany("bt_qi1o4tnuowtl6kla"),
	 oxorany("bt_db9psem55bg8u5hi"),
	 oxorany("bt_0kyhzdm46iy71lgi"),
	 oxorany("bt_wnacrj2xxoro4ru1"),
	 oxorany("bt_6dexlt5ol55drg9o"),
	 oxorany("bt_4qyw69l1tzeurx5p"),
	 oxorany("bt_q20xk0jqe1z2q0j6"),
	 oxorany("bt_7073n2w4ia7uqcpg"),
	 oxorany("bt_icq1oxl57dqa4d80"),
	 oxorany("bt_eugdbinau4jrcxvm"),
	 oxorany("bt_87zj6h4fovrisihf"),
	 oxorany("bt_a8hmczqad90mu0n7"),
	 oxorany("bt_94eqcls723g3xexw"),
	 oxorany("bt_ee9oa9g468wnvetx"),
	 oxorany("bt_irsgcieajmmhojjz"),
	 oxorany("bt_4hb2em8o5u8hracz"),
	 oxorany("bt_bqle2m4ygwx5zvil"),
	 oxorany("bt_1jwp482qh899zgy8"),
	 oxorany("bt_pg0jc7c8gqdu7h5x"),
	 oxorany("bt_dkk2xlzopdxaxjlm"),
	 oxorany("bt_9av91n2pi0p6fhf1"),
	 oxorany("bt_v8zhxm2jjwr1gheb"),
	 oxorany("bt_buh50zab7yr0wioy"),
	 oxorany("bt_9il17wymb5ehpd2n"),
	 oxorany("bt_a02wo9z3s4h4oize"),
	 oxorany("bt_v53nk21mud2revmt"),
	 oxorany("bt_6s95ktvhpqkbg5nd"),
	 oxorany("bt_022tsftrij27an9m"),
	 oxorany("bt_dp3vtav0kdzwvgme"),
	 oxorany("bt_5pv8hpuka7bbmth7")
	};
	std::vector<std::string> keys2 = {
	 oxorany("bt_sjfn27wx42x894ir"),
	 oxorany("bt_bw5cy42yac2zabko"),
	 oxorany("bt_xcdhxkbqso0z7xnp"),
	 oxorany("bt_vsalrmx9eve4drv0"),
	 oxorany("bt_ud7nfvpz7xq2w6ih"),
	 oxorany("bt_zzclw3oa2v2ozxww"),
	 oxorany("bt_15mgiaflzmkwo8mp"),
	 oxorany("bt_kdkt4ij63ckrxpyh"),
	 oxorany("bt_yn9lzshzn2mdxz5e"),
	 oxorany("bt_han143upyischrm6"),
	 oxorany("bt_gt306znyc2e4169n"),
	 oxorany("bt_r8ljx726f7ta0jww"),
	 oxorany("bt_7lukw36eouervxam"),
	 oxorany("bt_kupuoywybieippk0"),
	 oxorany("bt_h6toldy7mbbg21qn"),
	 oxorany("bt_ig2ko3a8y4xjoi2x"),
	 oxorany("bt_sg8ryw1jv3d87srz"),
	 oxorany("bt_6m4mlysle797qkdr"),
	 oxorany("bt_5y42izh1qen1zqva"),
	 oxorany("bt_b3cr5aesl2wujwec"),
	 oxorany("bt_gfrzyfaannzinvgn"),
	 oxorany("bt_ym1ksq5vjytg1zl1"),
	 oxorany("bt_kzh6wiq13hbm7dnf"),
	 oxorany("bt_i18wajqmmrqc5zum"),
	 oxorany("bt_kqyuftzrkoc4xq52"),
	 oxorany("bt_xmo9obv4oyht4yp7"),
	 oxorany("bt_lky4fpb35pminxea"),
	 oxorany("bt_082vc4sn0e9bav2h"),
	 oxorany("bt_3uljd9bmvu0asxuh"),
	 oxorany("bt_tu5mqkdh8us596ff"),
	 oxorany("bt_o744w1rn41o5hstb"),
	 oxorany("bt_ylihcoifogtpt7nn"),
	 oxorany("bt_dpj3c4nga5gkph09"),
	 oxorany("bt_j444ch46brb2x6hy"),
	 oxorany("bt_rou0yf8ewkmxwk7r"),
	 oxorany("bt_953du7f16vl3l3xo"),
	 oxorany("bt_7lswlbuw4qjge2e2"),
	 oxorany("bt_3k23oywk65x9g0ef"),
	 oxorany("bt_wq2mletjhk7k1orh"),
	 oxorany("bt_zzerof914e29nq7y"),
	 oxorany("bt_nptjeu13mgaedtb5"),
	 oxorany("bt_t2qw0s9s4iu7dtnr"),
	 oxorany("bt_41n0hibys6m23gw0"),
	 oxorany("bt_w4xc1lw3aewtui7j"),
	 oxorany("bt_7qspua3npqfql6fl"),
	 oxorany("bt_4rezo3844vq6uy8d"),
	 oxorany("bt_qf17fu5os0xgx2zr"),
	 oxorany("bt_3ebmpbu776eo7n03"),
	 oxorany("bt_iz8qem4eidkwjmqc"),
	 oxorany("bt_h030fka2ktm9h7ip"),
	 oxorany("bt_nmdh3ip1m3km00e9"),
	 oxorany("bt_6m9rvxd11t46bogn"),
	 oxorany("bt_ss2947rjo1gpqjka"),
	 oxorany("bt_tzxlw7rkmjlgpf54"),
	 oxorany("bt_2208enga9rieqasj"),
	 oxorany("bt_27xinwm6z78cil3m"),
	 oxorany("bt_e0ztqrmmrzg5aw3a"),
	 oxorany("bt_7hjv36h3qlfaugpc"),
	 oxorany("bt_o1we5r4a5g7stf2g"),
	 oxorany("bt_nz0kvjno43bu7y45"),
	 oxorany("bt_3qzc3w5418qx4tr0"),
	 oxorany("bt_58lsu56yr914d7ur"),
	 oxorany("bt_hredyctdxyfwkxuo"),
	 oxorany("bt_ljgvp3bx0bu3r1ns"),
	 oxorany("bt_zcjxgdurp7gdh4zt"),
	 oxorany("bt_jqmf7vk56zdmk47c"),
	 oxorany("bt_i88xu6j35suj2rid"),
	 oxorany("bt_tgm61h71jsd1ptrm"),
	 oxorany("bt_ae3giq8tse2zt23k"),
	 oxorany("bt_9ha1grb2sud9qdhf"),
	 oxorany("bt_hzwc4486vq0scd0h"),
	 oxorany("bt_n0kdxkwqbh3d2nqv"),
	 oxorany("bt_69ti71j2lfd8ynlh"),
	 oxorany("bt_asx4fal9dd14kk92"),
	 oxorany("bt_d19g3pzi554fvbvj"),
	 oxorany("bt_tblgr5aqw3bvuakh"),
	 oxorany("bt_iqranijwa4pd9tn5"),
	 oxorany("bt_hcfw1ejhq17lbix0"),
	 oxorany("bt_8w1k0fmemz5kkt5w"),
	 oxorany("bt_d5pxyk8k8kr1wgdy"),
	 oxorany("bt_chrsp1qphsc7kssq"),
	 oxorany("bt_0gxklab5e5wpctib"),
	 oxorany("bt_7depe2hoqe91uwt3"),
	 oxorany("bt_a3sn39fdzmyk4zeu"),
	 oxorany("bt_8coh63kwtda59f52"),
	 oxorany("bt_4k3ywvjueo2zasb4"),
	 oxorany("bt_a3kohf3k7d1mmjdz"),
	 oxorany("bt_w54prlnnog66gmpz"),
	 oxorany("bt_o4bwapdhm7v0eqg5"),
	 oxorany("bt_egur5nyizhd92rya"),
	 oxorany("bt_j4x357rqw94muyxm"),
	 oxorany("bt_ozpo7qd5aimtmxdr"),
	 oxorany("bt_afapsztgdwc6e2vo"),
	 oxorany("bt_ycate1ccax9rim0i"),
	 oxorany("bt_6htm6pjf4s2x57vw"),
	 oxorany("bt_xteeejrrhl4zldn2"),
	 oxorany("bt_l3o9j7hmk0km36pq"),
	 oxorany("bt_wt539hiwiy8s17v3"),
	 oxorany("bt_6zh0814qgkr0fylj"),
	 oxorany("bt_4kqyj550u1o8itcd"),
	 oxorany("bt_6it6smseprzms6iv"),
	 oxorany("bt_ya369fz71z6nra58"),
	 oxorany("bt_y69d3ktf65rkwqip"),
	 oxorany("bt_a8awa6ld1b8d4xt8"),
	 oxorany("bt_zr2000355xx1f0fi"),
	 oxorany("bt_ubo76crrysi6bqwy"),
	 oxorany("bt_wrawuvfmw1r0p3y6"),
	 oxorany("bt_rncw7rprzmua320k"),
	 oxorany("bt_yn6rs0spfo8wr6zr"),
	 oxorany("bt_jdcm5eemier2w7sg"),
	 oxorany("bt_5m8254wcw0jl1mek"),
	 oxorany("bt_93rfnl4f8a9lmylv"),
	 oxorany("bt_ikknptxgs44z1aqb"),
	 oxorany("bt_qzgk4cp544u44n8w"),
	 oxorany("bt_g01pjjdo3yp7sz66"),
	 oxorany("bt_z71o01utpmhuof8o"),
	 oxorany("bt_blaymaht3awj8blp"),
	 oxorany("bt_ld4g1beflexvbsxf"),
	 oxorany("bt_awfuvw1e544idcnj"),
	 oxorany("bt_wepnoejyweayyoto"),
	 oxorany("bt_m3zuhm1cltvargap"),
	 oxorany("bt_mbdu32kx0sr7xdnz"),
	 oxorany("bt_qnau9xbugs5s1p1t"),
	 oxorany("bt_t85906shkbyfetum"),
	 oxorany("bt_q4wlhzehmwtco2zb"),
	 oxorany("bt_k2zqdg9tmaha4bwy"),
	 oxorany("bt_er6ozapttakxkbws"),
	 oxorany("bt_wrc9fogymbxzraf6"),
	 oxorany("bt_f0gr7kk2wcjb8nfk"),
	 oxorany("bt_scfhqjvfohtqn5cb"),
	 oxorany("bt_wi7h8j475fbnhpoa"),
	 oxorany("bt_k9ei7jjpccrdegqo"),
	 oxorany("bt_28fytplzn1kl3cj7"),
	 oxorany("bt_sffq18m1rspbkyj8"),
	 oxorany("bt_47zzocfdcqq5njbe"),
	 oxorany("bt_6dcujz0v56walih1"),
	 oxorany("bt_lpyspfdbn1pt8ntz"),
	 oxorany("bt_avjev8wnwb5imc61"),
	 oxorany("bt_4vjsvqn3k1objdlo"),
	 oxorany("bt_ob960inj3nhhqlbz"),
	 oxorany("bt_ynbwut2iwhg4y6nz"),
	 oxorany("bt_aa64juusej8gufrg"),
	 oxorany("bt_2r7fqwqanbxx1nz9"),
	 oxorany("bt_w1wxsmkh1kdmk4xs"),
	 oxorany("bt_kewmsbgvfpnc65k5"),
	 oxorany("bt_muvzpjmr0zo5yi1y"),
	 oxorany("bt_z9lh8utcexycaycv"),
	 oxorany("bt_t7wkofke1uo09mp8"),
	 oxorany("bt_b09nktiu872eeep1"),
	 oxorany("bt_c7ch9rml0n049ogm"),
	 oxorany("bt_vpnottu14wh3hpko"),
	 oxorany("bt_89qdlrk10gvi1xl6"),
	 oxorany("bt_9c9ppkr81wzf53t3"),
	 oxorany("bt_v35pwwtlz4d41ksp"),
	 oxorany("bt_9vs7hzr7kc9a3oj8"),
	 oxorany("bt_uv10wk30zvhiissw"),
	 oxorany("bt_msfafnfeb2nbjdje"),
	 oxorany("bt_8jnct9r86spyw8q3"),
	 oxorany("bt_jccyyuj4wf8xnc7k"),
	 oxorany("bt_j2071p1omiyc31e7"),
	 oxorany("bt_h45quibsfn8ond7p"),
	 oxorany("bt_94ih9mprl18838sx"),
	 oxorany("bt_jasd5xbmw4kxz8bk"),
	 oxorany("bt_hwu3pi67rsmkycoy"),
	 oxorany("bt_p8ive2m1sxuwpo4a"),
	 oxorany("bt_rokk1nq2vtlm6fhe"),
	 oxorany("bt_w576j62zmj69nroa"),
	 oxorany("bt_28xog9yahsxus1ph"),
	 oxorany("bt_roubgpwmqnomwtkd"),
	 oxorany("bt_vepp6t3uxza10nqq"),
	 oxorany("bt_qi1o4tnuowtl6kla"),
	 oxorany("bt_db9psem55bg8u5hi"),
	 oxorany("bt_0kyhzdm46iy71lgi"),
	 oxorany("bt_wnacrj2xxoro4ru1"),
	 oxorany("bt_6dexlt5ol55drg9o"),
	 oxorany("bt_4qyw69l1tzeurx5p"),
	 oxorany("bt_q20xk0jqe1z2q0j6"),
	 oxorany("bt_7073n2w4ia7uqcpg"),
	 oxorany("bt_icq1oxl57dqa4d80"),
	 oxorany("bt_eugdbinau4jrcxvm"),
	 oxorany("bt_87zj6h4fovrisihf"),
	 oxorany("bt_a8hmczqad90mu0n7"),
	 oxorany("bt_94eqcls723g3xexw"),
	 oxorany("bt_ee9oa9g468wnvetx"),
	 oxorany("bt_irsgcieajmmhojjz"),
	 oxorany("bt_4hb2em8o5u8hracz"),
	 oxorany("bt_bqle2m4ygwx5zvil"),
	 oxorany("bt_1jwp482qh899zgy8"),
	 oxorany("bt_pg0jc7c8gqdu7h5x"),
	 oxorany("bt_dkk2xlzopdxaxjlm"),
	 oxorany("bt_9av91n2pi0p6fhf1"),
	 oxorany("bt_v8zhxm2jjwr1gheb"),
	 oxorany("bt_buh50zab7yr0wioy"),
	 oxorany("bt_9il17wymb5ehpd2n"),
	 oxorany("bt_a02wo9z3s4h4oize"),
	 oxorany("bt_v53nk21mud2revmt"),
	 oxorany("bt_6s95ktvhpqkbg5nd"),
	 oxorany("bt_022tsftrij27an9m"),
	 oxorany("bt_dp3vtav0kdzwvgme"),
	 oxorany("bt_5pv8hpuka7bbmth7")
	};
	std::vector<std::string> keys3 = {
	 oxorany("bt_sjfn27wx42x894ir"),
	 oxorany("bt_bw5cy42yac2zabko"),
	 oxorany("bt_xcdhxkbqso0z7xnp"),
	 oxorany("bt_vsalrmx9eve4drv0"),
	 oxorany("bt_ud7nfvpz7xq2w6ih"),
	 oxorany("bt_zzclw3oa2v2ozxww"),
	 oxorany("bt_15mgiaflzmkwo8mp"),
	 oxorany("bt_kdkt4ij63ckrxpyh"),
	 oxorany("bt_yn9lzshzn2mdxz5e"),
	 oxorany("bt_han143upyischrm6"),
	 oxorany("bt_gt306znyc2e4169n"),
	 oxorany("bt_r8ljx726f7ta0jww"),
	 oxorany("bt_7lukw36eouervxam"),
	 oxorany("bt_kupuoywybieippk0"),
	 oxorany("bt_h6toldy7mbbg21qn"),
	 oxorany("bt_ig2ko3a8y4xjoi2x"),
	 oxorany("bt_sg8ryw1jv3d87srz"),
	 oxorany("bt_6m4mlysle797qkdr"),
	 oxorany("bt_5y42izh1qen1zqva"),
	 oxorany("bt_b3cr5aesl2wujwec"),
	 oxorany("bt_gfrzyfaannzinvgn"),
	 oxorany("bt_ym1ksq5vjytg1zl1"),
	 oxorany("bt_kzh6wiq13hbm7dnf"),
	 oxorany("bt_i18wajqmmrqc5zum"),
	 oxorany("bt_kqyuftzrkoc4xq52"),
	 oxorany("bt_xmo9obv4oyht4yp7"),
	 oxorany("bt_lky4fpb35pminxea"),
	 oxorany("bt_082vc4sn0e9bav2h"),
	 oxorany("bt_3uljd9bmvu0asxuh"),
	 oxorany("bt_tu5mqkdh8us596ff"),
	 oxorany("bt_o744w1rn41o5hstb"),
	 oxorany("bt_ylihcoifogtpt7nn"),
	 oxorany("bt_dpj3c4nga5gkph09"),
	 oxorany("bt_j444ch46brb2x6hy"),
	 oxorany("bt_rou0yf8ewkmxwk7r"),
	 oxorany("bt_953du7f16vl3l3xo"),
	 oxorany("bt_7lswlbuw4qjge2e2"),
	 oxorany("bt_3k23oywk65x9g0ef"),
	 oxorany("bt_wq2mletjhk7k1orh"),
	 oxorany("bt_zzerof914e29nq7y"),
	 oxorany("bt_nptjeu13mgaedtb5"),
	 oxorany("bt_t2qw0s9s4iu7dtnr"),
	 oxorany("bt_41n0hibys6m23gw0"),
	 oxorany("bt_w4xc1lw3aewtui7j"),
	 oxorany("bt_7qspua3npqfql6fl"),
	 oxorany("bt_4rezo3844vq6uy8d"),
	 oxorany("bt_qf17fu5os0xgx2zr"),
	 oxorany("bt_3ebmpbu776eo7n03"),
	 oxorany("bt_iz8qem4eidkwjmqc"),
	 oxorany("bt_h030fka2ktm9h7ip"),
	 oxorany("bt_nmdh3ip1m3km00e9"),
	 oxorany("bt_6m9rvxd11t46bogn"),
	 oxorany("bt_ss2947rjo1gpqjka"),
	 oxorany("bt_tzxlw7rkmjlgpf54"),
	 oxorany("bt_2208enga9rieqasj"),
	 oxorany("bt_27xinwm6z78cil3m"),
	 oxorany("bt_e0ztqrmmrzg5aw3a"),
	 oxorany("bt_7hjv36h3qlfaugpc"),
	 oxorany("bt_o1we5r4a5g7stf2g"),
	 oxorany("bt_nz0kvjno43bu7y45"),
	 oxorany("bt_3qzc3w5418qx4tr0"),
	 oxorany("bt_58lsu56yr914d7ur"),
	 oxorany("bt_hredyctdxyfwkxuo"),
	 oxorany("bt_ljgvp3bx0bu3r1ns"),
	 oxorany("bt_zcjxgdurp7gdh4zt"),
	 oxorany("bt_jqmf7vk56zdmk47c"),
	 oxorany("bt_i88xu6j35suj2rid"),
	 oxorany("bt_tgm61h71jsd1ptrm"),
	 oxorany("bt_ae3giq8tse2zt23k"),
	 oxorany("bt_9ha1grb2sud9qdhf"),
	 oxorany("bt_hzwc4486vq0scd0h"),
	 oxorany("bt_n0kdxkwqbh3d2nqv"),
	 oxorany("bt_69ti71j2lfd8ynlh"),
	 oxorany("bt_asx4fal9dd14kk92"),
	 oxorany("bt_d19g3pzi554fvbvj"),
	 oxorany("bt_tblgr5aqw3bvuakh"),
	 oxorany("bt_iqranijwa4pd9tn5"),
	 oxorany("bt_hcfw1ejhq17lbix0"),
	 oxorany("bt_8w1k0fmemz5kkt5w"),
	 oxorany("bt_d5pxyk8k8kr1wgdy"),
	 oxorany("bt_chrsp1qphsc7kssq"),
	 oxorany("bt_0gxklab5e5wpctib"),
	 oxorany("bt_7depe2hoqe91uwt3"),
	 oxorany("bt_a3sn39fdzmyk4zeu"),
	 oxorany("bt_8coh63kwtda59f52"),
	 oxorany("bt_4k3ywvjueo2zasb4"),
	 oxorany("bt_a3kohf3k7d1mmjdz"),
	 oxorany("bt_w54prlnnog66gmpz"),
	 oxorany("bt_o4bwapdhm7v0eqg5"),
	 oxorany("bt_egur5nyizhd92rya"),
	 oxorany("bt_j4x357rqw94muyxm"),
	 oxorany("bt_ozpo7qd5aimtmxdr"),
	 oxorany("bt_afapsztgdwc6e2vo"),
	 oxorany("bt_ycate1ccax9rim0i"),
	 oxorany("bt_6htm6pjf4s2x57vw"),
	 oxorany("bt_xteeejrrhl4zldn2"),
	 oxorany("bt_l3o9j7hmk0km36pq"),
	 oxorany("bt_wt539hiwiy8s17v3"),
	 oxorany("bt_6zh0814qgkr0fylj"),
	 oxorany("bt_4kqyj550u1o8itcd"),
	 oxorany("bt_6it6smseprzms6iv"),
	 oxorany("bt_ya369fz71z6nra58"),
	 oxorany("bt_y69d3ktf65rkwqip"),
	 oxorany("bt_a8awa6ld1b8d4xt8"),
	 oxorany("bt_zr2000355xx1f0fi"),
	 oxorany("bt_ubo76crrysi6bqwy"),
	 oxorany("bt_wrawuvfmw1r0p3y6"),
	 oxorany("bt_rncw7rprzmua320k"),
	 oxorany("bt_yn6rs0spfo8wr6zr"),
	 oxorany("bt_jdcm5eemier2w7sg"),
	 oxorany("bt_5m8254wcw0jl1mek"),
	 oxorany("bt_93rfnl4f8a9lmylv"),
	 oxorany("bt_ikknptxgs44z1aqb"),
	 oxorany("bt_qzgk4cp544u44n8w"),
	 oxorany("bt_g01pjjdo3yp7sz66"),
	 oxorany("bt_z71o01utpmhuof8o"),
	 oxorany("bt_blaymaht3awj8blp"),
	 oxorany("bt_ld4g1beflexvbsxf"),
	 oxorany("bt_awfuvw1e544idcnj"),
	 oxorany("bt_wepnoejyweayyoto"),
	 oxorany("bt_m3zuhm1cltvargap"),
	 oxorany("bt_mbdu32kx0sr7xdnz"),
	 oxorany("bt_qnau9xbugs5s1p1t"),
	 oxorany("bt_t85906shkbyfetum"),
	 oxorany("bt_q4wlhzehmwtco2zb"),
	 oxorany("bt_k2zqdg9tmaha4bwy"),
	 oxorany("bt_er6ozapttakxkbws"),
	 oxorany("bt_wrc9fogymbxzraf6"),
	 oxorany("bt_f0gr7kk2wcjb8nfk"),
	 oxorany("bt_scfhqjvfohtqn5cb"),
	 oxorany("bt_wi7h8j475fbnhpoa"),
	 oxorany("bt_k9ei7jjpccrdegqo"),
	 oxorany("bt_28fytplzn1kl3cj7"),
	 oxorany("bt_sffq18m1rspbkyj8"),
	 oxorany("bt_47zzocfdcqq5njbe"),
	 oxorany("bt_6dcujz0v56walih1"),
	 oxorany("bt_lpyspfdbn1pt8ntz"),
	 oxorany("bt_avjev8wnwb5imc61"),
	 oxorany("bt_4vjsvqn3k1objdlo"),
	 oxorany("bt_ob960inj3nhhqlbz"),
	 oxorany("bt_ynbwut2iwhg4y6nz"),
	 oxorany("bt_aa64juusej8gufrg"),
	 oxorany("bt_2r7fqwqanbxx1nz9"),
	 oxorany("bt_w1wxsmkh1kdmk4xs"),
	 oxorany("bt_kewmsbgvfpnc65k5"),
	 oxorany("bt_muvzpjmr0zo5yi1y"),
	 oxorany("bt_z9lh8utcexycaycv"),
	 oxorany("bt_t7wkofke1uo09mp8"),
	 oxorany("bt_b09nktiu872eeep1"),
	 oxorany("bt_c7ch9rml0n049ogm"),
	 oxorany("bt_vpnottu14wh3hpko"),
	 oxorany("bt_89qdlrk10gvi1xl6"),
	 oxorany("bt_9c9ppkr81wzf53t3"),
	 oxorany("bt_v35pwwtlz4d41ksp"),
	 oxorany("bt_9vs7hzr7kc9a3oj8"),
	 oxorany("bt_uv10wk30zvhiissw"),
	 oxorany("bt_msfafnfeb2nbjdje"),
	 oxorany("bt_8jnct9r86spyw8q3"),
	 oxorany("bt_jccyyuj4wf8xnc7k"),
	 oxorany("bt_j2071p1omiyc31e7"),
	 oxorany("bt_h45quibsfn8ond7p"),
	 oxorany("bt_94ih9mprl18838sx"),
	 oxorany("bt_jasd5xbmw4kxz8bk"),
	 oxorany("bt_hwu3pi67rsmkycoy"),
	 oxorany("bt_p8ive2m1sxuwpo4a"),
	 oxorany("bt_rokk1nq2vtlm6fhe"),
	 oxorany("bt_w576j62zmj69nroa"),
	 oxorany("bt_28xog9yahsxus1ph"),
	 oxorany("bt_roubgpwmqnomwtkd"),
	 oxorany("bt_vepp6t3uxza10nqq"),
	 oxorany("bt_qi1o4tnuowtl6kla"),
	 oxorany("bt_db9psem55bg8u5hi"),
	 oxorany("bt_0kyhzdm46iy71lgi"),
	 oxorany("bt_wnacrj2xxoro4ru1"),
	 oxorany("bt_6dexlt5ol55drg9o"),
	 oxorany("bt_4qyw69l1tzeurx5p"),
	 oxorany("bt_q20xk0jqe1z2q0j6"),
	 oxorany("bt_7073n2w4ia7uqcpg"),
	 oxorany("bt_icq1oxl57dqa4d80"),
	 oxorany("bt_eugdbinau4jrcxvm"),
	 oxorany("bt_87zj6h4fovrisihf"),
	 oxorany("bt_a8hmczqad90mu0n7"),
	 oxorany("bt_94eqcls723g3xexw"),
	 oxorany("bt_ee9oa9g468wnvetx"),
	 oxorany("bt_irsgcieajmmhojjz"),
	 oxorany("bt_4hb2em8o5u8hracz"),
	 oxorany("bt_bqle2m4ygwx5zvil"),
	 oxorany("bt_1jwp482qh899zgy8"),
	 oxorany("bt_pg0jc7c8gqdu7h5x"),
	 oxorany("bt_dkk2xlzopdxaxjlm"),
	 oxorany("bt_9av91n2pi0p6fhf1"),
	 oxorany("bt_v8zhxm2jjwr1gheb"),
	 oxorany("bt_buh50zab7yr0wioy"),
	 oxorany("bt_9il17wymb5ehpd2n"),
	 oxorany("bt_a02wo9z3s4h4oize"),
	 oxorany("bt_v53nk21mud2revmt"),
	 oxorany("bt_6s95ktvhpqkbg5nd"),
	 oxorany("bt_022tsftrij27an9m"),
	 oxorany("bt_dp3vtav0kdzwvgme"),
	 oxorany("bt_5pv8hpuka7bbmth7")
	};
  ImDrawList* draw = ImGui::GetBackgroundDrawList();
  if(!c_vars->p_players)return;
  const auto& typinfo = *reinterpret_cast<uintptr_t*>(base_addr + oxorany(125781608));
  if(typinfo){
      const auto& lazysingleton = *reinterpret_cast<uintptr_t*>(typinfo + oxorany(0x58));
      if(lazysingleton){
          const auto& statik = *reinterpret_cast<uintptr_t*>(lazysingleton + oxorany(0xB8));
          if(statik){
              const auto& inst = *reinterpret_cast<uintptr_t*>(statik + oxorany(0x0));
              if(inst){
                  if(!*reinterpret_cast<uintptr_t*>( inst + oxorany(0x80) ))return;
                  const auto &dict = *reinterpret_cast<monoDictionary<int, uintptr_t>**>( inst + oxorany(0x28));
                  if(dict != nullptr && dict->getValues().size() != oxorany(0)) vec = dict->getValues();
                  local = *reinterpret_cast<uintptr_t*>( inst + oxorany(0x80) );
                  camera_pos = game_sdk->get_position(game_sdk->get_transform(game_sdk->camera()));

              }
          }
      }
  }
  for(const auto& target : vec){
    if(!local || !*reinterpret_cast<uintptr_t*>(local + oxorany(0x130)))return;
    if(!target)continue;
    const auto& pton = *reinterpret_cast<uintptr_t*>(target + oxorany(0x130));
    if(!pton)continue;
    if(*reinterpret_cast<uint8_t*>(target + oxorany(0x59)) == *reinterpret_cast<uint8_t*>(local + oxorany(0x59)))continue;

    const auto& occl = *reinterpret_cast<uintptr_t*>(target + oxorany(0x90));
    game_sdk->set_visible(occl, true);
    game_sdk->set_enabled(occl, false);
    *reinterpret_cast<bool*>(occl + oxorany(0x30)) = false;
    *reinterpret_cast<bool*>(occl + oxorany(0x31)) = false;
    *reinterpret_cast<bool*>(occl + oxorany(0x32)) = false;
    const auto& pos = game_sdk->get_position(game_sdk->get_transform(target));
    bool check;
    const auto& dist = Vector3::Distance(camera_pos, pos);
    const auto& clapped = dist / oxorany(100);
    const auto& bottom = game_sdk->w_checker(pos - Vector3(oxorany(0),oxorany_flt(0.1),oxorany(0)), check);
    const auto& top = game_sdk->w_checker(pos + Vector3(oxorany(0),oxorany_flt(1.9),oxorany(0)), check);
    auto top_pos = top.x;
    auto bot_pos = bottom.x;
    if (top.x > bottom.x) { top_pos = bottom.x; bot_pos = top.x; }
    const float& width = fabs((top.y - bottom.y) / (oxorany_flt(2.5) + clapped));
    ImRect rect = ImRect(ImVec2(bottom.x - width, bottom.y), ImVec2(top.x + width, top.y));
    if(!check)continue;
    if(c_vars->p_skeletone){
    draw->AddLine(bone_v2(target, oxorany(0x20)), bone_v2(target, oxorany(0x28)), ImColor(oxorany_flt(255), oxorany_flt(255), oxorany_flt(255)));
    draw->AddLine(bone_v2(target, oxorany(0x28)), bone_v2(target, oxorany(0x80)), ImColor(oxorany_flt(255), oxorany_flt(255), oxorany_flt(255)));
    draw->AddLine(bone_v2(target, oxorany(0x28)), bone_v2(target, oxorany(0x48)), ImColor(oxorany_flt(255), oxorany_flt(255), oxorany_flt(255)));
    draw->AddLine(bone_v2(target, oxorany(0x28)), bone_v2(target, oxorany(0x68)), ImColor(oxorany_flt(255), oxorany_flt(255), oxorany_flt(255)));
    draw->AddLine(bone_v2(target, oxorany(0x48)), bone_v2(target, oxorany(0x50)), ImColor(oxorany_flt(255), oxorany_flt(255), oxorany_flt(255)));
    draw->AddLine(bone_v2(target, oxorany(0x50)), bone_v2(target, oxorany(0x58)), ImColor(oxorany_flt(255), oxorany_flt(255), oxorany_flt(255)));
    draw->AddLine(bone_v2(target, oxorany(0x68)), bone_v2(target, oxorany(0x70)), ImColor(oxorany_flt(255), oxorany_flt(255), oxorany_flt(255)));
    draw->AddLine(bone_v2(target, oxorany(0x70)), bone_v2(target, oxorany(0x78)), ImColor(oxorany_flt(255), oxorany_flt(255), oxorany_flt(255)));
    draw->AddLine(bone_v2(target, oxorany(0x80)), bone_v2(target, oxorany(0x90)), ImColor(oxorany_flt(255), oxorany_flt(255), oxorany_flt(255)));
    draw->AddLine(bone_v2(target, oxorany(0x90)), bone_v2(target, oxorany(0x98)), ImColor(oxorany_flt(255), oxorany_flt(255), oxorany_flt(255)));
    draw->AddLine(bone_v2(target, oxorany(0x80)), bone_v2(target, oxorany(0xA8)), ImColor(oxorany_flt(255), oxorany_flt(255), oxorany_flt(255)));
    draw->AddLine(bone_v2(target, oxorany(0xA8)), bone_v2(target, oxorany(0xB0)), ImColor(oxorany_flt(255), oxorany_flt(255), oxorany_flt(255)));
    }
    if(c_vars->p_box){
      draw->AddRect(rect.Min - ImVec2(oxorany(0.5), oxorany(0.5)), rect.Max + ImVec2(oxorany(0.5), oxorany(0.5)), ImColor(oxorany(0), oxorany(0), oxorany(0), oxorany(200)), oxorany(0), oxorany(0), oxorany(0.6));
      draw->AddRect(rect.Min + ImVec2(oxorany(0.5), oxorany(0.5)), rect.Max - ImVec2(oxorany(0.5), oxorany(0.5)), ImColor(oxorany(0), oxorany(0), oxorany(0), 200), oxorany(0), oxorany(0), oxorany(0.6));
      draw->AddRect(rect.Min, rect.Max, ImColor(oxorany(255),oxorany(255),oxorany(255)));
    }
    if(c_vars->p_name){
      auto name = *reinterpret_cast<monoString**>( pton + oxorany(0x20));
      const auto& nam = name->toCPPString();
      const auto& text_size = verdana_small->calc_size(8, nam);
      const auto& text_pos = ImVec2( rect.Min.x + (rect.GetWidth() / oxorany(2)) - text_size.x / oxorany(2), rect.Max.y - oxorany(2) - text_size.y );
      AddText(verdana_small, oxorany(8), false, true, text_pos, ImColor(oxorany(255),oxorany(255),oxorany(255)), nam);
    }
    if(c_vars->p_chams){
    //const auto& mesh = game_sdk->get_mesh(*reinterpret_cast<uintptr_t*>(target + oxorany(0x100)));


    }
    if(c_vars->p_aim){
      const auto& bipedmap = *reinterpret_cast<uintptr_t*>(*reinterpret_cast<uintptr_t*>(target + oxorany(0xA8)) + oxorany(0x58));
      if(!bipedmap)continue;
      const auto& head = *reinterpret_cast<uintptr_t*>(bipedmap + oxorany(0x20));
      if(!head)continue;
      const auto& headpos = game_sdk->get_position(head);
      const auto& aimcontroller = *reinterpret_cast<uintptr_t*>(local + oxorany(0x60));
      const auto& adata = *reinterpret_cast<uintptr_t*>(aimcontroller + oxorany(0x98));
      if(infov(game_sdk->w_regular(headpos)) && !linecast(headpos)){
       *reinterpret_cast<Vector3*>(adata + oxorany(0x18)) = ToEulerRad(Quaternion::LookRotation(headpos - camera_pos));
        *reinterpret_cast<Vector3*>(adata + oxorany(0x24)) = ToEulerRad(Quaternion::LookRotation(headpos - camera_pos));
      }
    }
  }
if(c_vars->p_aim){
                    draw->AddCircle(disp.wh / oxorany(2), (float)c_vars->aim_fov, ImColor(oxorany(255),oxorany(255),oxorany(255)), oxorany(999), oxorany(0.6f));
                  }
}


HOOKAF(void, h5gg){
  return;
}
