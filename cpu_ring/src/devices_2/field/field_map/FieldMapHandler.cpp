#include "FieldMapHandler.h"

FieldMapHandler::FieldMapHandler(const string& map_name, const shared_ptr<physics::FieldMapData>& data, const unique_ptr<physics::CoordConverter>& converter): mapName(map_name),
                                                                                                                                                               data(data),
                                                                                                                                                               converter(converter)
{
}