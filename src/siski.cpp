#include <leonardavinc.hpp>


ACTION leonardavinc::setfee(name collection, float genfee) {
  
  require_auth(get_self());

  feedatatb feetb(_self, _self.value);

  const auto& feerow = feetb.find(collection.value);
                   
  if (feerow == feetb.end()) {
  feetb.emplace(_self, [&](auto& item) {
    item.genfee = genfee;
    item.collection = collection;
  });
}
                  else { 
    feetb.modify( feerow, _self, [&](auto& item) {
    item.genfee = genfee;
                       });    
}


}



ACTION leonardavinc::mint(name accname, string nftname, string cid) {
  require_auth(accname);

  tracking_table _tracks(get_self(), get_self().value);

  auto track_itr = _tracks.find(accname.value);

  if (track_itr != _tracks.end()) {

  const auto& itr=_tracks.get(accname.value, "You have not paid for minting, my friend." );

   check (itr.minted != 0, "You have already minted NFT.");

    _tracks.modify(track_itr, _self, [&](auto& track) {
      track.minted = 0;
        });
  } 
  else{
  check(false, "You have not paid for minting, my friend.");
  }


atomicassets::ATTRIBUTE_MAP immutable_data = {};

immutable_data["name"] = string(nftname);

immutable_data["img"] = string(cid);




name authorized_minter = "alienfractal"_n;

name collection_name = "dallepapsidd"_n;

//atomicassets::ATTRIBUTE_MAP immutable_data = [{name:"pede",img:"Qmc5eYBJ73h5NZX7rsk6gCqNR9HsyLpLakNYiNUCFuRYYx"}];

atomicassets::ATTRIBUTE_MAP mutable_data = {};

name new_asset_owner = accname;

name schema_name = "dalleschemak"_n;

int32_t template_id = 597107;

vector<asset> tokens_to_back = {};


//[{"key": "name", "value": ["string", "nimi"]}, {"key": "img", "value": ["string", "Qmc5eYBJ73h5NZX7rsk6gCqNR9HsyLpLakNYiNUCFuRYYx"]}]

//{"key":"name","value":["string","nimi"]}{"key":"img","value":["string","Qmc5eYBJ73h5NZX7rsk6gCqNR9HsyLpLakNYiNUCFuRYYx"]}

//{"key":"name","value":["string","nimi"]}{"key":"img","value":["string","Qmc5eYBJ73h5NZX7rsk6gCqNR9HsyLpLakNYiNUCFuRYYx"]}

mintasset(authorized_minter, collection_name,schema_name,template_id,new_asset_owner,immutable_data,mutable_data,tokens_to_back);

}







ACTION leonardavinc::generation(name accname) {
  
  require_auth(get_self());

  tracking_table _tracks(get_self(), get_self().value);

  auto track_itr = _tracks.find(accname.value);

  //const auto& track_itr=_tracks.get(accname.value, "You have not paid for the generation, my friend." );

  if (track_itr != _tracks.end()) {

  const auto& itr=_tracks.get(accname.value, "You have not paid for the generation, my friend." );

   check (itr.generated != 0, "You have already generated images.");

    _tracks.modify(track_itr, _self, [&](auto& track) {
      track.generated = 0;
        });
  } 
  else 
  {
  check(false, "You have not paid for the generation, my friend.");
  }
}
