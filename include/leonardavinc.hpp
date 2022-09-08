#include <eosio/eosio.hpp>
#include <atomicassets-interface.hpp>


using namespace std;
using namespace eosio;

CONTRACT leonardavinc : public contract {
  public:
    using contract::contract;

    ACTION mint(name accname, string nftname, string cid);
    ACTION setfee(name collection, float genfee);
    ACTION generation(name accname);

[[eosio::on_notify("eosio.token::transfer")]]
  void initact (name from, name to, asset quantity, std::string memo);

  private:



  void mintasset(name authorized_minter, name collection_name, name schema_name, int32_t template_id, name new_asset_owner, atomicassets::ATTRIBUTE_MAP immutable_data,
 atomicassets::ATTRIBUTE_MAP mutable_data, vector<asset> tokens_to_back) {
    
      action(
      permission_level{get_self(),"active"_n},
      "atomicassets"_n,
      "mintasset"_n,
      std::make_tuple(authorized_minter,collection_name,schema_name,template_id,new_asset_owner,immutable_data,mutable_data,tokens_to_back)
    ).send();
  };


void send(name from, name to, asset quantity, std::string memo) {
    
      action(
      permission_level{get_self(),"active"_n},
      "eosio.token"_n,
      "transfer"_n,
      std::make_tuple(from,to,quantity,memo)
    ).send();
  };




    TABLE tracking {
      name    accname;
      uint8_t generated;
      uint8_t minted;
      auto primary_key() const { return accname.value; }
    };
    typedef multi_index<name("tracking"), tracking> tracking_table;


  


TABLE feedata {

float genfee;

name collection;

auto primary_key() const { return collection.value; }
    };
typedef eosio::multi_index<name("feedata"), feedata > feedatatb;



TABLE datapoints {
    uint64_t id;
    name owner; 
    uint64_t value;
    uint64_t median;
    time_point timestamp;

    uint64_t primary_key() const {return id;}
    uint64_t by_timestamp() const {return timestamp.elapsed.to_seconds();}
    uint64_t by_value() const {return value;}

  };

   typedef eosio::multi_index<"datapoints"_n, datapoints,
      indexed_by<"value"_n, const_mem_fun<datapoints, uint64_t, &datapoints::by_value>>, 
      indexed_by<"timestamp"_n, const_mem_fun<datapoints, uint64_t, &datapoints::by_timestamp>>> datapointstable;







};









//endcontract


